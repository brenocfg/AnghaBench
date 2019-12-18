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
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;

/* Variables and functions */
 struct lpfc_nodelist* __lpfc_find_node (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_filter_by_rpi ; 

struct lpfc_nodelist *
__lpfc_findnode_rpi(struct lpfc_vport *vport, uint16_t rpi)
{
	return __lpfc_find_node(vport, lpfc_filter_by_rpi, &rpi);
}