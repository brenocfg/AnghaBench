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
struct nisplus_search_callback_data {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  nis_object ;
typedef  int /*<<< orphan*/  nis_name ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_LEN (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ENTRY_VAL (int /*<<< orphan*/  const*,int) ; 
 int TRUE ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strnsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nisplus_search_callback(const nis_name key, const nis_object *value, voidp opaquedata)
{
  struct nisplus_search_callback_data *data = (struct nisplus_search_callback_data *) opaquedata;

  dlog("NISplus search callback for <%s>", ENTRY_VAL(value, 0));
  dlog("NISplus search callback value <%s>", ENTRY_VAL(value, 1));

  data->value = strnsave(ENTRY_VAL(value, 1), ENTRY_LEN(value, 1));
  return TRUE;
}