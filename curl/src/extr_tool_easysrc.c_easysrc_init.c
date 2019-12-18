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

CURLcode easysrc_init(void)
{
  CHKRET(easysrc_add(&easysrc_code,
                     "hnd = curl_easy_init();"));
  return CURLE_OK;
}