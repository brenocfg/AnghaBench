#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct libipw_qos_parameters {int dummy; } ;
struct TYPE_3__ {int ac_info; } ;
struct libipw_qos_parameter_info {TYPE_1__ info_element; } ;
struct libipw_qos_information_element {int ac_info; } ;
struct TYPE_4__ {int param_count; int supported; struct libipw_qos_parameters parameters; } ;
struct libipw_network {TYPE_2__ qos_data; int /*<<< orphan*/  flags; } ;
struct libipw_info_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBIPW_DEBUG_QOS (char*) ; 
 int /*<<< orphan*/  NETWORK_HAS_QOS_INFORMATION ; 
 int /*<<< orphan*/  NETWORK_HAS_QOS_PARAMETERS ; 
 int /*<<< orphan*/  libipw_qos_convert_ac_to_parameters (struct libipw_qos_parameter_info*,struct libipw_qos_parameters*) ; 
 int libipw_read_qos_info_element (struct libipw_qos_information_element*,struct libipw_info_element*) ; 
 int libipw_read_qos_param_element (struct libipw_qos_parameter_info*,struct libipw_info_element*) ; 

__attribute__((used)) static int libipw_parse_qos_info_param_IE(struct libipw_info_element
					     *info_element,
					     struct libipw_network *network)
{
	int rc = 0;
	struct libipw_qos_parameters *qos_param = NULL;
	struct libipw_qos_information_element qos_info_element;

	rc = libipw_read_qos_info_element(&qos_info_element, info_element);

	if (rc == 0) {
		network->qos_data.param_count = qos_info_element.ac_info & 0x0F;
		network->flags |= NETWORK_HAS_QOS_INFORMATION;
	} else {
		struct libipw_qos_parameter_info param_element;

		rc = libipw_read_qos_param_element(&param_element,
						      info_element);
		if (rc == 0) {
			qos_param = &(network->qos_data.parameters);
			libipw_qos_convert_ac_to_parameters(&param_element,
							       qos_param);
			network->flags |= NETWORK_HAS_QOS_PARAMETERS;
			network->qos_data.param_count =
			    param_element.info_element.ac_info & 0x0F;
		}
	}

	if (rc == 0) {
		LIBIPW_DEBUG_QOS("QoS is supported\n");
		network->qos_data.supported = 1;
	}
	return rc;
}