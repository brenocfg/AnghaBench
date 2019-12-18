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
struct zfcp_fsf_cfdc {int /*<<< orphan*/  option; void* command; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FSF_CFDC_OPTION_FORCE ; 
 int /*<<< orphan*/  FSF_CFDC_OPTION_FULL_ACCESS ; 
 int /*<<< orphan*/  FSF_CFDC_OPTION_NORMAL_MODE ; 
 int /*<<< orphan*/  FSF_CFDC_OPTION_RESTRICTED_ACCESS ; 
 void* FSF_QTCB_DOWNLOAD_CONTROL_FILE ; 
 void* FSF_QTCB_UPLOAD_CONTROL_FILE ; 
#define  ZFCP_CFDC_CMND_DOWNLOAD_FORCE 132 
#define  ZFCP_CFDC_CMND_DOWNLOAD_NORMAL 131 
#define  ZFCP_CFDC_CMND_FULL_ACCESS 130 
#define  ZFCP_CFDC_CMND_RESTRICTED_ACCESS 129 
#define  ZFCP_CFDC_CMND_UPLOAD 128 

__attribute__((used)) static int zfcp_cfdc_set_fsf(struct zfcp_fsf_cfdc *fsf_cfdc, int command)
{
	switch (command) {
	case ZFCP_CFDC_CMND_DOWNLOAD_NORMAL:
		fsf_cfdc->command = FSF_QTCB_DOWNLOAD_CONTROL_FILE;
		fsf_cfdc->option = FSF_CFDC_OPTION_NORMAL_MODE;
		break;
	case ZFCP_CFDC_CMND_DOWNLOAD_FORCE:
		fsf_cfdc->command = FSF_QTCB_DOWNLOAD_CONTROL_FILE;
		fsf_cfdc->option = FSF_CFDC_OPTION_FORCE;
		break;
	case ZFCP_CFDC_CMND_FULL_ACCESS:
		fsf_cfdc->command = FSF_QTCB_DOWNLOAD_CONTROL_FILE;
		fsf_cfdc->option = FSF_CFDC_OPTION_FULL_ACCESS;
		break;
	case ZFCP_CFDC_CMND_RESTRICTED_ACCESS:
		fsf_cfdc->command = FSF_QTCB_DOWNLOAD_CONTROL_FILE;
		fsf_cfdc->option = FSF_CFDC_OPTION_RESTRICTED_ACCESS;
		break;
	case ZFCP_CFDC_CMND_UPLOAD:
		fsf_cfdc->command = FSF_QTCB_UPLOAD_CONTROL_FILE;
		fsf_cfdc->option = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}