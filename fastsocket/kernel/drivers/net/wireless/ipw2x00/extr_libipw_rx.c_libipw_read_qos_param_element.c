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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ elementID; scalar_t__ length; int /*<<< orphan*/  qui; } ;
struct libipw_qos_parameter_info {TYPE_1__ info_element; } ;
struct libipw_info_element {scalar_t__ id; scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ QOS_ELEMENT_ID ; 
 int /*<<< orphan*/  QOS_OUI_PARAM_SUB_TYPE ; 
 int libipw_verify_qos_info (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int libipw_read_qos_param_element(struct libipw_qos_parameter_info
					    *element_param, struct libipw_info_element
					    *info_element)
{
	int ret = 0;
	u16 size = sizeof(struct libipw_qos_parameter_info) - 2;

	if ((info_element == NULL) || (element_param == NULL))
		return -1;

	if (info_element->id == QOS_ELEMENT_ID && info_element->len == size) {
		memcpy(element_param->info_element.qui, info_element->data,
		       info_element->len);
		element_param->info_element.elementID = info_element->id;
		element_param->info_element.length = info_element->len;
	} else
		ret = -1;
	if (ret == 0)
		ret = libipw_verify_qos_info(&element_param->info_element,
						QOS_OUI_PARAM_SUB_TYPE);
	return ret;
}