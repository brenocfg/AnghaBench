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
typedef  int /*<<< orphan*/  curl_lock_data ;
typedef  int /*<<< orphan*/  curl_lock_access ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void my_lock(CURL *handle, curl_lock_data data,
                    curl_lock_access laccess, void *useptr)
{
  (void)handle;
  (void)data;
  (void)laccess;
  (void)useptr;
  fprintf(stderr, "-> Mutex lock\n");
}