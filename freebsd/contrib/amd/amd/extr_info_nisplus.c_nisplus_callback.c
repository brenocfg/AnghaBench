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
typedef  scalar_t__ voidp ;
struct nis_callback_data {int /*<<< orphan*/  ncd_m; int /*<<< orphan*/  (* ncd_fn ) (int /*<<< orphan*/ ,char*,char*) ;} ;
typedef  int /*<<< orphan*/  nis_object ;
typedef  int /*<<< orphan*/  nis_name ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_LEN (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ENTRY_VAL (int /*<<< orphan*/  const*,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  dlog (char*,char*,char*) ; 
 char* strnsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
nisplus_callback(const nis_name key, const nis_object *value, voidp opaquedata)
{
  char *kp = strnsave(ENTRY_VAL(value, 0), ENTRY_LEN(value, 0));
  char *vp = strnsave(ENTRY_VAL(value, 1), ENTRY_LEN(value, 1));
  struct nis_callback_data *data = (struct nis_callback_data *) opaquedata;

  dlog("NISplus callback for <%s,%s>", kp, vp);

  (*data->ncd_fn) (data->ncd_m, kp, vp);

  /*
   * We want more ...
   */
  return FALSE;
}