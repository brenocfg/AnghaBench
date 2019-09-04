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
struct sockopt {int dummy; } ;
struct ip_fw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  IP_FW_CURRENT_API_VERSION 130 
#define  IP_FW_VERSION_0 129 
#define  IP_FW_VERSION_1 128 
 int ipfw_version_one_to_latest_32 (struct sockopt*,struct ip_fw*,int /*<<< orphan*/ *) ; 
 int ipfw_version_one_to_latest_64 (struct sockopt*,struct ip_fw*,int /*<<< orphan*/ *) ; 

int
ipfw_convert_to_latest(struct sockopt *sopt, struct ip_fw *curr_rule, int api_version, int is64user)
{
	int	err = 0;
	
	/* the following functions copy the rules passed in and
	 * convert to latest structures based on version
	 */
	switch (api_version) {
		case IP_FW_VERSION_0:
			/* we're not supporting VERSION 0 */
			err = EOPNOTSUPP;
			break;
		
		case IP_FW_VERSION_1:
			/* this is the version supported in Panther */
			if ( is64user )
				err = ipfw_version_one_to_latest_64(sopt, curr_rule, NULL);
			else
				err = ipfw_version_one_to_latest_32(sopt, curr_rule, NULL);
			break;
		
		case IP_FW_CURRENT_API_VERSION:
			/* IPFW2 for now */
			/* do nothing here... */
			break;
		
		default:
			/* unrecognized/unsupported version */
			err = EINVAL;
			break;
	}
	
	return err;
}