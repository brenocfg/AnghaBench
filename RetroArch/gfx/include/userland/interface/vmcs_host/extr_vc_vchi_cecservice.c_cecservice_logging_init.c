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

/* Variables and functions */
 int /*<<< orphan*/  VCOS_LOG_WARN ; 
 int /*<<< orphan*/  cechost_log_category ; 
 int cecservice_log_initialised ; 
 int /*<<< orphan*/  vc_cec_log_info (char*) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cecservice_logging_init() {
   if(cecservice_log_initialised == 0) {
      vcos_log_set_level(&cechost_log_category, VCOS_LOG_WARN);
      vcos_log_register("cecservice-client", &cechost_log_category);
      vc_cec_log_info("CEC HOST: log initialised");
      cecservice_log_initialised = 1;
   }
}