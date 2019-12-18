#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  method; int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ httpd_uri_t ;
typedef  int /*<<< orphan*/  httpd_handle_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int HTTPD_TEST_MAX_URI_HANDLERS ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int basic_sanity ; 
 TYPE_1__ handler_limit_uri (char*) ; 
 scalar_t__ httpd_register_uri_handler (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ httpd_unregister_uri_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_digits (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void test_handler_limit(httpd_handle_t hd)
{
    int i;
    char x[HTTPD_TEST_MAX_URI_HANDLERS+1][num_digits(HTTPD_TEST_MAX_URI_HANDLERS)+1];
    httpd_uri_t uris[HTTPD_TEST_MAX_URI_HANDLERS+1];

    for (i = 0; i < HTTPD_TEST_MAX_URI_HANDLERS + 1; i++) {
        sprintf(x[i],"%d",i);
        uris[i] = handler_limit_uri(x[i]);
    }

    /* Register multiple instances of the same handler for MAX URI Handlers */
    for (i = 0; i < HTTPD_TEST_MAX_URI_HANDLERS; i++) {
        TEST_ASSERT(httpd_register_uri_handler(hd, &uris[i]) == ESP_OK);
    }

    /* Register the MAX URI + 1 Handlers should fail */
    TEST_ASSERT(httpd_register_uri_handler(hd, &uris[HTTPD_TEST_MAX_URI_HANDLERS]) != ESP_OK);

    /* Unregister the one of the Handler should pass */
    TEST_ASSERT(httpd_unregister_uri_handler(hd, uris[0].uri, uris[0].method) == ESP_OK);

    /* Unregister non added Handler should fail */
    TEST_ASSERT(httpd_unregister_uri_handler(hd, uris[0].uri, uris[0].method) != ESP_OK);

    /* Register the MAX URI Handler should pass */
    TEST_ASSERT(httpd_register_uri_handler(hd, &uris[0]) == ESP_OK);

    /* Reregister same instance of handler should fail */
    TEST_ASSERT(httpd_register_uri_handler(hd, &uris[0]) != ESP_OK);

    /* Register the MAX URI + 1 Handlers should fail */
    TEST_ASSERT(httpd_register_uri_handler(hd, &uris[HTTPD_TEST_MAX_URI_HANDLERS]) != ESP_OK);

    /* Unregister the same handler for MAX URI Handlers */
    for (i = 0; i < HTTPD_TEST_MAX_URI_HANDLERS; i++) {
        TEST_ASSERT(httpd_unregister_uri_handler(hd, uris[i].uri, uris[i].method) == ESP_OK);
    }
    basic_sanity = false;
}