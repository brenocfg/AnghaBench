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
struct Curl_share {int specifier; int /*<<< orphan*/  hostcache; } ;

/* Variables and functions */
 int CURL_LOCK_DATA_SHARE ; 
 scalar_t__ Curl_mk_dnscache (int /*<<< orphan*/ *) ; 
 struct Curl_share* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct Curl_share*) ; 

struct Curl_share *
curl_share_init(void)
{
  struct Curl_share *share = calloc(1, sizeof(struct Curl_share));
  if(share) {
    share->specifier |= (1<<CURL_LOCK_DATA_SHARE);

    if(Curl_mk_dnscache(&share->hostcache)) {
      free(share);
      return NULL;
    }
  }

  return share;
}