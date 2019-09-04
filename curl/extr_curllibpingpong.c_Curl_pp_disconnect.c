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
struct pingpong {int /*<<< orphan*/ * cache; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

CURLcode Curl_pp_disconnect(struct pingpong *pp)
{
  free(pp->cache);
  pp->cache = NULL;
  return CURLE_OK;
}