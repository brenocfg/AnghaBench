#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sierra_net_data {int /*<<< orphan*/  tx_hdr_template; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void build_hip(u8 *buf, const u16 payloadlen,
		struct sierra_net_data *priv)
{
	/* the following doesn't have the full functionality. We
	 * currently build only one kind of header, so it is faster this way
	 */
	put_unaligned_be16(payloadlen, buf);
	memcpy(buf+2, priv->tx_hdr_template, sizeof(priv->tx_hdr_template));
}