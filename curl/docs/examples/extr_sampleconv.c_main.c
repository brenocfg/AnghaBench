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
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_CONV_FROM_NETWORK_FUNCTION ; 
 int /*<<< orphan*/  CURLOPT_CONV_FROM_UTF8_FUNCTION ; 
 int /*<<< orphan*/  CURLOPT_CONV_TO_NETWORK_FUNCTION ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * curl_easy_init () ; 
 int /*<<< orphan*/  curl_easy_perform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* my_conv_from_ascii_to_ebcdic ; 
 char* my_conv_from_ebcdic_to_ascii ; 
 char* my_conv_from_utf8_to_ebcdic ; 

int main(void)
{
  CURL *curl;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");

    /* use platform-specific functions for codeset conversions */
    curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                     my_conv_from_ascii_to_ebcdic);
    curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_FUNCTION,
                     my_conv_from_ebcdic_to_ascii);
    curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION,
                     my_conv_from_utf8_to_ebcdic);

    curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}