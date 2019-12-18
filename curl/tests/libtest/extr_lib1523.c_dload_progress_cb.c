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
typedef  int /*<<< orphan*/  curl_off_t ;

/* Variables and functions */

__attribute__((used)) static int dload_progress_cb(void *a, curl_off_t b, curl_off_t c,
                             curl_off_t d, curl_off_t e)
{
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  (void)e;
  return 0;
}