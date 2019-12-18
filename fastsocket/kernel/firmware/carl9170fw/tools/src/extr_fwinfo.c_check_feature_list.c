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
struct feature_list {int id; char* name; int /*<<< orphan*/  (* func ) (struct carl9170fw_desc_head const*,struct carlfw*) ;} ;
struct carlfw {int dummy; } ;
struct carl9170fw_desc_head {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  carl9170fw_supports (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stub1 (struct carl9170fw_desc_head const*,struct carlfw*) ; 

__attribute__((used)) static void check_feature_list(const struct carl9170fw_desc_head *head,
			       const __le32 bitmap,
			       const struct feature_list *list,
			       const unsigned int entries,
			       struct carlfw *fw)
{
	unsigned int i;

	for (i = 0; i < entries; i++) {
		if (!carl9170fw_supports(bitmap, list[i].id))
			continue;

		fprintf(stdout, "\t\t%2d = %s\n", list[i].id, list[i].name);
		if (list[i].func)
			list[i].func(head, fw);
	}
}