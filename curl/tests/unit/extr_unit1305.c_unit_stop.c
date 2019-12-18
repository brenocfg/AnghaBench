#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_freeaddrinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_global_cleanup () ; 
 int /*<<< orphan*/  data ; 
 TYPE_1__* data_key ; 
 TYPE_1__* data_node ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hp ; 

__attribute__((used)) static void unit_stop(void)
{
  if(data_node) {
    Curl_freeaddrinfo(data_node->addr);
    free(data_node);
  }
  free(data_key);
  Curl_hash_destroy(&hp);

  curl_easy_cleanup(data);
  curl_global_cleanup();
}