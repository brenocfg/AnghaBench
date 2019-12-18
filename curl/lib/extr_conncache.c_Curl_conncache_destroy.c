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
struct conncache {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_hash_destroy (int /*<<< orphan*/ *) ; 

void Curl_conncache_destroy(struct conncache *connc)
{
  if(connc)
    Curl_hash_destroy(&connc->hash);
}