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
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 int TDATA_SIZE ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  apr_itoa (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix ; 
 int /*<<< orphan*/  randval (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txt ; 

__attribute__((used)) static int create_test_hash(apr_pool_t *p, apr_hash_t *h)
{
  int i;
  
  for (i = 0; i < TDATA_SIZE; i++) {
    char *k, *v;
    
    k = apr_pstrcat(p, prefix, apr_itoa(p, i), NULL);
    v = apr_pstrndup(p, txt, randval((apr_uint32_t)strlen(txt)));
    
    apr_hash_set(h, k, APR_HASH_KEY_STRING, v);
  }

  return i;
}