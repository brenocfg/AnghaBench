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
 size_t CURL_READFUNC_ABORT ; 

__attribute__((used)) static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  (void)ptr;
  (void)size;
  (void)nmemb;
  (void)userp;
  return CURL_READFUNC_ABORT;
}