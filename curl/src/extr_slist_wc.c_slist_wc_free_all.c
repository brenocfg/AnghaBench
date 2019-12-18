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
struct slist_wc {int /*<<< orphan*/  first; } ;

/* Variables and functions */
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct slist_wc*) ; 

void slist_wc_free_all(struct slist_wc *list)
{
  if(!list)
    return;

  curl_slist_free_all(list->first);
  free(list);
}