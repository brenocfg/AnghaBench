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
typedef  int /*<<< orphan*/  u32 ;
struct request_context {int dummy; } ;
struct hermes {struct ezusb_priv* priv; } ;
struct ezusb_priv {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EZUSB_FRAME_CONTROL ; 
 int /*<<< orphan*/  EZUSB_RID_ACK ; 
 int /*<<< orphan*/  EZUSB_RID_PROG_INIT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ezusb_access_ltv (struct ezusb_priv*,struct request_context*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct request_context* ezusb_alloc_ctx (struct ezusb_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ezusb_program_init(struct hermes *hw, u32 entry_point)
{
	struct ezusb_priv *upriv = hw->priv;
	struct request_context *ctx;
	__le32 data = cpu_to_le32(entry_point);

	ctx = ezusb_alloc_ctx(upriv, EZUSB_RID_PROG_INIT, EZUSB_RID_ACK);
	if (!ctx)
		return -ENOMEM;

	return ezusb_access_ltv(upriv, ctx, sizeof(data), &data,
				EZUSB_FRAME_CONTROL, NULL, 0, NULL);
}