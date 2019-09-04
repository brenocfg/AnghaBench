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
struct Curl_multi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_CONNECTION_HASH_SIZE ; 
 int /*<<< orphan*/  CURL_SOCKET_HASH_TABLE_SIZE ; 
 struct Curl_multi* Curl_multi_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct Curl_multi *curl_multi_init(void)
{
  return Curl_multi_handle(CURL_SOCKET_HASH_TABLE_SIZE,
                           CURL_CONNECTION_HASH_SIZE);
}