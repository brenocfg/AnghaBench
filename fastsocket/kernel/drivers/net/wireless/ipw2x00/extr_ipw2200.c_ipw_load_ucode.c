#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int alive_command; int ucode_valid; int /*<<< orphan*/ * time_stamp; int /*<<< orphan*/  device_identifier; int /*<<< orphan*/  software_revision; } ;
struct ipw_priv {TYPE_1__ dino_alive; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DINO_ENABLE_CS ; 
 int DINO_ENABLE_SYSTEM ; 
 int DINO_RXFIFO_DATA ; 
 int EINVAL ; 
 int ETIME ; 
 int /*<<< orphan*/  IPW_BASEBAND_CONTROL_STATUS ; 
 int /*<<< orphan*/  IPW_BASEBAND_CONTROL_STORE ; 
 int /*<<< orphan*/  IPW_BASEBAND_POWER_DOWN ; 
 int /*<<< orphan*/  IPW_BASEBAND_RX_FIFO_READ ; 
 int /*<<< orphan*/  IPW_BIT_HALT_RESET_OFF ; 
 int /*<<< orphan*/  IPW_BIT_HALT_RESET_ON ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,...) ; 
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 int /*<<< orphan*/  IPW_INTERNAL_CMD_EVENT ; 
 int /*<<< orphan*/  IPW_MEM_HALT_AND_RESET ; 
 int IPW_REGISTER_DOMAIN1_END ; 
 int IPW_SHARED_LOWER_BOUND ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_arc_release (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_read_reg32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int ipw_read_reg8 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int ipw_stop_master (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg16 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg8 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipw_load_ucode(struct ipw_priv *priv, u8 * data, size_t len)
{
	int rc = 0, i, addr;
	u8 cr = 0;
	__le16 *image;

	image = (__le16 *) data;

	IPW_DEBUG_TRACE(">>\n");

	rc = ipw_stop_master(priv);

	if (rc < 0)
		return rc;

	for (addr = IPW_SHARED_LOWER_BOUND;
	     addr < IPW_REGISTER_DOMAIN1_END; addr += 4) {
		ipw_write32(priv, addr, 0);
	}

	/* no ucode (yet) */
	memset(&priv->dino_alive, 0, sizeof(priv->dino_alive));
	/* destroy DMA queues */
	/* reset sequence */

	ipw_write_reg32(priv, IPW_MEM_HALT_AND_RESET, IPW_BIT_HALT_RESET_ON);
	ipw_arc_release(priv);
	ipw_write_reg32(priv, IPW_MEM_HALT_AND_RESET, IPW_BIT_HALT_RESET_OFF);
	mdelay(1);

	/* reset PHY */
	ipw_write_reg32(priv, IPW_INTERNAL_CMD_EVENT, IPW_BASEBAND_POWER_DOWN);
	mdelay(1);

	ipw_write_reg32(priv, IPW_INTERNAL_CMD_EVENT, 0);
	mdelay(1);

	/* enable ucode store */
	ipw_write_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, 0x0);
	ipw_write_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, DINO_ENABLE_CS);
	mdelay(1);

	/* write ucode */
	/**
	 * @bug
	 * Do NOT set indirect address register once and then
	 * store data to indirect data register in the loop.
	 * It seems very reasonable, but in this case DINO do not
	 * accept ucode. It is essential to set address each time.
	 */
	/* load new ipw uCode */
	for (i = 0; i < len / 2; i++)
		ipw_write_reg16(priv, IPW_BASEBAND_CONTROL_STORE,
				le16_to_cpu(image[i]));

	/* enable DINO */
	ipw_write_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, 0);
	ipw_write_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, DINO_ENABLE_SYSTEM);

	/* this is where the igx / win driver deveates from the VAP driver. */

	/* wait for alive response */
	for (i = 0; i < 100; i++) {
		/* poll for incoming data */
		cr = ipw_read_reg8(priv, IPW_BASEBAND_CONTROL_STATUS);
		if (cr & DINO_RXFIFO_DATA)
			break;
		mdelay(1);
	}

	if (cr & DINO_RXFIFO_DATA) {
		/* alive_command_responce size is NOT multiple of 4 */
		__le32 response_buffer[(sizeof(priv->dino_alive) + 3) / 4];

		for (i = 0; i < ARRAY_SIZE(response_buffer); i++)
			response_buffer[i] =
			    cpu_to_le32(ipw_read_reg32(priv,
						       IPW_BASEBAND_RX_FIFO_READ));
		memcpy(&priv->dino_alive, response_buffer,
		       sizeof(priv->dino_alive));
		if (priv->dino_alive.alive_command == 1
		    && priv->dino_alive.ucode_valid == 1) {
			rc = 0;
			IPW_DEBUG_INFO
			    ("Microcode OK, rev. %d (0x%x) dev. %d (0x%x) "
			     "of %02d/%02d/%02d %02d:%02d\n",
			     priv->dino_alive.software_revision,
			     priv->dino_alive.software_revision,
			     priv->dino_alive.device_identifier,
			     priv->dino_alive.device_identifier,
			     priv->dino_alive.time_stamp[0],
			     priv->dino_alive.time_stamp[1],
			     priv->dino_alive.time_stamp[2],
			     priv->dino_alive.time_stamp[3],
			     priv->dino_alive.time_stamp[4]);
		} else {
			IPW_DEBUG_INFO("Microcode is not alive\n");
			rc = -EINVAL;
		}
	} else {
		IPW_DEBUG_INFO("No alive response from DINO\n");
		rc = -ETIME;
	}

	/* disable DINO, otherwise for some reason
	   firmware have problem getting alive resp. */
	ipw_write_reg8(priv, IPW_BASEBAND_CONTROL_STATUS, 0);

	return rc;
}