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
struct Curl_multi {int maxconnects; int /*<<< orphan*/  pending; int /*<<< orphan*/  msglist; int /*<<< orphan*/  conn_cache; int /*<<< orphan*/  hostcache; int /*<<< orphan*/  sockhash; int /*<<< orphan*/  multiplexing; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_MULTI_HANDLE ; 
 int /*<<< orphan*/  Curl_conncache_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_conncache_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Curl_hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_llist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Curl_mk_dnscache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 struct Curl_multi* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct Curl_multi*) ; 
 scalar_t__ sh_init (int /*<<< orphan*/ *,int) ; 

struct Curl_multi *Curl_multi_handle(int hashsize, /* socket hash */
                                     int chashsize) /* connection hash */
{
  struct Curl_multi *multi = calloc(1, sizeof(struct Curl_multi));

  if(!multi)
    return NULL;

  multi->type = CURL_MULTI_HANDLE;

  if(Curl_mk_dnscache(&multi->hostcache))
    goto error;

  if(sh_init(&multi->sockhash, hashsize))
    goto error;

  if(Curl_conncache_init(&multi->conn_cache, chashsize))
    goto error;

  Curl_llist_init(&multi->msglist, NULL);
  Curl_llist_init(&multi->pending, NULL);

  multi->multiplexing = TRUE;

  /* -1 means it not set by user, use the default value */
  multi->maxconnects = -1;
  return multi;

  error:

  Curl_hash_destroy(&multi->sockhash);
  Curl_hash_destroy(&multi->hostcache);
  Curl_conncache_destroy(&multi->conn_cache);
  Curl_llist_destroy(&multi->msglist, NULL);
  Curl_llist_destroy(&multi->pending, NULL);

  free(multi);
  return NULL;
}