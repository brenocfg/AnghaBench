#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cami2c {TYPE_1__* msg; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int addr; int len; } ;

/* Variables and functions */
 int FCR_RFRST ; 
 int FCR_TFRST ; 
 int FIER_RXIE ; 
 int FIFO_SIZE ; 
 int /*<<< orphan*/  I2CFCR ; 
 int /*<<< orphan*/  I2CFIER ; 
 int /*<<< orphan*/  I2CMAR ; 
 int /*<<< orphan*/  I2CMCR ; 
 int /*<<< orphan*/  I2CMIER ; 
 int /*<<< orphan*/  I2CMSR ; 
 int /*<<< orphan*/  I2CSAR ; 
 int /*<<< orphan*/  IDF_RECV ; 
 int MCR_ESG ; 
 int MCR_MIE ; 
 int MIE_MALE ; 
 int MIE_MATE ; 
 int MIE_MNRE ; 
 int MIE_MSTE ; 
 int /*<<< orphan*/  OUT32 (struct cami2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh7760_i2c_mrecv(struct cami2c *id)
{
	int len;

	id->flags |= IDF_RECV;

	/* set the slave addr reg; otherwise rcv wont work! */
	OUT32(id, I2CSAR, 0xfe);
	OUT32(id, I2CMAR, (id->msg->addr << 1) | 1);

	/* adjust rx fifo trigger */
	if (id->msg->len >= FIFO_SIZE)
		len = FIFO_SIZE - 1;	/* trigger at fifo full */
	else
		len = id->msg->len - 1;	/* trigger before all received */

	OUT32(id, I2CFCR, FCR_RFRST | FCR_TFRST);
	OUT32(id, I2CFCR, FCR_TFRST | ((len & 0xF) << 4));

	OUT32(id, I2CMSR, 0);
	OUT32(id, I2CMCR, MCR_MIE | MCR_ESG);
	OUT32(id, I2CMIER, MIE_MNRE | MIE_MALE | MIE_MSTE | MIE_MATE);
	OUT32(id, I2CFIER, FIER_RXIE);
}