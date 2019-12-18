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
struct Curl_share {size_t max_ssl_sessions; int /*<<< orphan*/  clientdata; int /*<<< orphan*/  (* unlockfunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  psl; struct Curl_share* sslsession; int /*<<< orphan*/  cookies; int /*<<< orphan*/  hostcache; int /*<<< orphan*/  conn_cache; scalar_t__ dirty; int /*<<< orphan*/  (* lockfunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CURLSHcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLSHE_INVALID ; 
 int /*<<< orphan*/  CURLSHE_IN_USE ; 
 int /*<<< orphan*/  CURLSHE_OK ; 
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_SHARE ; 
 int /*<<< orphan*/  Curl_conncache_close_all_connections (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_conncache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_cookie_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_hash_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_psl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_ssl_kill_session (struct Curl_share*) ; 
 int /*<<< orphan*/  free (struct Curl_share*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CURLSHcode
curl_share_cleanup(struct Curl_share *share)
{
  if(share == NULL)
    return CURLSHE_INVALID;

  if(share->lockfunc)
    share->lockfunc(NULL, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE,
                    share->clientdata);

  if(share->dirty) {
    if(share->unlockfunc)
      share->unlockfunc(NULL, CURL_LOCK_DATA_SHARE, share->clientdata);
    return CURLSHE_IN_USE;
  }

  Curl_conncache_close_all_connections(&share->conn_cache);
  Curl_conncache_destroy(&share->conn_cache);
  Curl_hash_destroy(&share->hostcache);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
  Curl_cookie_cleanup(share->cookies);
#endif

#ifdef USE_SSL
  if(share->sslsession) {
    size_t i;
    for(i = 0; i < share->max_ssl_sessions; i++)
      Curl_ssl_kill_session(&(share->sslsession[i]));
    free(share->sslsession);
  }
#endif

  Curl_psl_destroy(&share->psl);

  if(share->unlockfunc)
    share->unlockfunc(NULL, CURL_LOCK_DATA_SHARE, share->clientdata);
  free(share);

  return CURLSHE_OK;
}