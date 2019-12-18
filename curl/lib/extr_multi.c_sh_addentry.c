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
 int /*<<< orphan*/  Curl_hash_add (struct curl_hash*,char*,int,struct Curl_sh_entry*) ; 
 scalar_t__ Curl_hash_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRHASH_SIZE ; 
 struct Curl_sh_entry* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct Curl_sh_entry*) ; 
 struct Curl_sh_entry* sh_getentry (struct curl_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trhash ; 
 int /*<<< orphan*/  trhash_compare ; 
 int /*<<< orphan*/  trhash_dtor ; 

__attribute__((used)) static struct Curl_sh_entry *sh_addentry(struct curl_hash *sh,
                                         curl_socket_t s)
{
  struct Curl_sh_entry *there = sh_getentry(sh, s);
  struct Curl_sh_entry *check;

  if(there) {
    /* it is present, return fine */
    return there;
  }

  /* not present, add it */
  check = calloc(1, sizeof(struct Curl_sh_entry));
  if(!check)
    return NULL; /* major failure */

  if(Curl_hash_init(&check->transfers, TRHASH_SIZE, trhash,
                    trhash_compare, trhash_dtor)) {
    free(check);
    return NULL;
  }

  /* make/add new hash entry */
  if(!Curl_hash_add(sh, (char *)&s, sizeof(curl_socket_t), check)) {
    free(check);
    return NULL; /* major failure */
  }

  return check; /* things are good in sockhash land */
}