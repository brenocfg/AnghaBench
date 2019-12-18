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
 int /*<<< orphan*/  TEST_DATA_STRING ; 
 int /*<<< orphan*/  cb_count ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
resolver_alloc_cb_fail(void *resolver_state, void *reserved, void *userdata)
{
  (void)resolver_state;
  (void)reserved;

  cb_count++;
  if(strcmp(userdata, TEST_DATA_STRING)) {
    fprintf(stderr, "Invalid test data received");
    exit(1);
  }

  return 1;
}