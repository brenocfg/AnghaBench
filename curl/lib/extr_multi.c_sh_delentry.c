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
struct curl_hash {int dummy; } ;
struct Curl_sh_entry {int /*<<< orphan*/  transfers; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_hash_delete (struct curl_hash*,char*,int) ; 
 int /*<<< orphan*/  Curl_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_delentry(struct Curl_sh_entry *entry,
                        struct curl_hash *sh, curl_socket_t s)
{
  Curl_hash_destroy(&entry->transfers);

  /* We remove the hash entry. This will end up in a call to
     sh_freeentry(). */
  Curl_hash_delete(sh, (char *)&s, sizeof(curl_socket_t));
}