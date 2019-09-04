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
struct Curl_URL {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct Curl_URL*) ; 
 int /*<<< orphan*/  free_urlhandle (struct Curl_URL*) ; 

__attribute__((used)) static void mv_urlhandle(struct Curl_URL *from,
                         struct Curl_URL *to)
{
  free_urlhandle(to);
  *to = *from;
  free(from);
}