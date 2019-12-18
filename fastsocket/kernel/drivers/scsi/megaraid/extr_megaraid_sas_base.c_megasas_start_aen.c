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
struct TYPE_2__ {int /*<<< orphan*/  class; int /*<<< orphan*/  locale; scalar_t__ reserved; } ;
union megasas_evt_class_locale {int /*<<< orphan*/  word; TYPE_1__ members; } ;
struct megasas_instance {int dummy; } ;
struct megasas_evt_log_info {scalar_t__ newest_seq_num; } ;
typedef  int /*<<< orphan*/  eli ;

/* Variables and functions */
 int /*<<< orphan*/  MR_EVT_CLASS_DEBUG ; 
 int /*<<< orphan*/  MR_EVT_LOCALE_ALL ; 
 scalar_t__ megasas_get_seq_num (struct megasas_instance*,struct megasas_evt_log_info*) ; 
 int megasas_register_aen (struct megasas_instance*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct megasas_evt_log_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int megasas_start_aen(struct megasas_instance *instance)
{
	struct megasas_evt_log_info eli;
	union megasas_evt_class_locale class_locale;

	/*
	 * Get the latest sequence number from FW
	 */
	memset(&eli, 0, sizeof(eli));

	if (megasas_get_seq_num(instance, &eli))
		return -1;

	/*
	 * Register AEN with FW for latest sequence number plus 1
	 */
	class_locale.members.reserved = 0;
	class_locale.members.locale = MR_EVT_LOCALE_ALL;
	class_locale.members.class = MR_EVT_CLASS_DEBUG;

	return megasas_register_aen(instance, eli.newest_seq_num + 1,
				    class_locale.word);
}