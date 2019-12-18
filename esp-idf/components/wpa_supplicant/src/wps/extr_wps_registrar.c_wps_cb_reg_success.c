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
struct wps_registrar {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* reg_success_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void wps_cb_reg_success(struct wps_registrar *reg, const u8 *mac_addr,
			       const u8 *uuid_e, const u8 *dev_pw,
			       size_t dev_pw_len)
{
	if (reg->reg_success_cb == NULL)
		return;

	reg->reg_success_cb(reg->cb_ctx, mac_addr, uuid_e, dev_pw, dev_pw_len);
}