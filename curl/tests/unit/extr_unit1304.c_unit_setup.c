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
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  login ; 
 int /*<<< orphan*/  password ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static CURLcode unit_setup(void)
{
  password = strdup("");
  login = strdup("");
  if(!password || !login) {
    Curl_safefree(password);
    Curl_safefree(login);
    return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}