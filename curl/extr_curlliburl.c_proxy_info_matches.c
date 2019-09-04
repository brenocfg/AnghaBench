#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct proxy_info {scalar_t__ proxytype; scalar_t__ port; TYPE_1__ host; } ;

/* Variables and functions */
 scalar_t__ Curl_safe_strcasecompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static bool
proxy_info_matches(const struct proxy_info* data,
                   const struct proxy_info* needle)
{
  if((data->proxytype == needle->proxytype) &&
     (data->port == needle->port) &&
     Curl_safe_strcasecompare(data->host.name, needle->host.name))
    return TRUE;

  return FALSE;
}