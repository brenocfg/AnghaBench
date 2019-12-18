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
struct connectbundle {int dummy; } ;
struct conncache {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 void* Curl_hash_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct connectbundle*) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool conncache_add_bundle(struct conncache *connc,
                                 char *key,
                                 struct connectbundle *bundle)
{
  void *p = Curl_hash_add(&connc->hash, key, strlen(key), bundle);

  return p?TRUE:FALSE;
}