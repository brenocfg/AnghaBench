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

/* Variables and functions */
 int /*<<< orphan*/  Curl_hash_clean_with_criterium (struct curl_hash*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
Curl_hash_clean(struct curl_hash *h)
{
  Curl_hash_clean_with_criterium(h, NULL, NULL);
}