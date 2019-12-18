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
struct curl_slist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTHEADER ; 
 struct curl_slist* curl_slist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct curl_slist *sethost(struct curl_slist *headers)
{
  (void)headers;
  return curl_slist_append(NULL, HOSTHEADER);
}