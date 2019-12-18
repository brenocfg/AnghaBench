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
typedef  int /*<<< orphan*/  apr_xml_parser ;
typedef  int /*<<< orphan*/  apr_xml_doc ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/ * apr_xml_parser_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_xml_parser_done (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_xml_parser_feed (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static void test_CVE_2009_3720_alpha(abts_case *tc, void *data)
{
    apr_xml_parser *xp;
    apr_xml_doc *doc;
    apr_status_t rv;

    xp = apr_xml_parser_create(p);
    
    rv = apr_xml_parser_feed(xp, "\0\r\n", 3);
    if (rv == APR_SUCCESS)
        apr_xml_parser_done(xp, &doc);
}