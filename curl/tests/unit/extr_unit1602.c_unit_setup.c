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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_hash_str ; 
 int /*<<< orphan*/  Curl_str_key_compare ; 
 int /*<<< orphan*/  hash_static ; 
 int /*<<< orphan*/  mydtor ; 

__attribute__((used)) static CURLcode unit_setup(void)
{
  return Curl_hash_init(&hash_static, 7, Curl_hash_str,
                        Curl_str_key_compare, mydtor);
}