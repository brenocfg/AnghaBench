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
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  expire_id ;

/* Variables and functions */
 int /*<<< orphan*/  multi_deltimeout (struct Curl_easy*,int /*<<< orphan*/ ) ; 

void Curl_expire_done(struct Curl_easy *data, expire_id id)
{
  /* remove the timer, if there */
  multi_deltimeout(data, id);
}