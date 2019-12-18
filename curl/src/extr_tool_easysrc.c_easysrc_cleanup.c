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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CHKRET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  easysrc_add (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  easysrc_code ; 

CURLcode easysrc_cleanup(void)
{
  CHKRET(easysrc_add(&easysrc_code, "curl_easy_cleanup(hnd);"));
  CHKRET(easysrc_add(&easysrc_code, "hnd = NULL;"));

  return CURLE_OK;
}