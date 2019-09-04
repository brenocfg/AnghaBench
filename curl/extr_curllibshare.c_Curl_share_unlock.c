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
struct Curl_share {int specifier; int /*<<< orphan*/  clientdata; int /*<<< orphan*/  (* unlockfunc ) (struct Curl_easy*,int,int /*<<< orphan*/ ) ;} ;
struct Curl_easy {struct Curl_share* share; } ;
typedef  int curl_lock_data ;
typedef  int /*<<< orphan*/  CURLSHcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLSHE_INVALID ; 
 int /*<<< orphan*/  CURLSHE_OK ; 
 int /*<<< orphan*/  stub1 (struct Curl_easy*,int,int /*<<< orphan*/ ) ; 

CURLSHcode
Curl_share_unlock(struct Curl_easy *data, curl_lock_data type)
{
  struct Curl_share *share = data->share;

  if(share == NULL)
    return CURLSHE_INVALID;

  if(share->specifier & (1<<type)) {
    if(share->unlockfunc) /* only call this if set! */
      share->unlockfunc (data, type, share->clientdata);
  }

  return CURLSHE_OK;
}