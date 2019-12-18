#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int id; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ CURLSSLBACKEND_NONE ; 
 TYPE_2__* Curl_ssl ; 
 int /*<<< orphan*/  multissl_init (int /*<<< orphan*/ *) ; 

int Curl_ssl_backend(void)
{
#ifdef USE_SSL
  multissl_init(NULL);
  return Curl_ssl->info.id;
#else
  return (int)CURLSSLBACKEND_NONE;
#endif
}