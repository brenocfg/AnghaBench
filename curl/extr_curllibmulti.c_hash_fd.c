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
typedef  size_t curl_socket_t ;

/* Variables and functions */

__attribute__((used)) static size_t hash_fd(void *key, size_t key_length, size_t slots_num)
{
  curl_socket_t fd = *((curl_socket_t *) key);
  (void) key_length;

  return (fd % slots_num);
}