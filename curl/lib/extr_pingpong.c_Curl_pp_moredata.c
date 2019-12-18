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
struct pingpong {scalar_t__ nread_resp; scalar_t__ cache_size; scalar_t__ cache; int /*<<< orphan*/  sendleft; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 

bool Curl_pp_moredata(struct pingpong *pp)
{
  return (!pp->sendleft && pp->cache && pp->nread_resp < pp->cache_size) ?
         TRUE : FALSE;
}