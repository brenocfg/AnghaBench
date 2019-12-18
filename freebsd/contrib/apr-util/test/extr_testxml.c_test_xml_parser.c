#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_xml_parser ;
struct TYPE_3__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ apr_xml_doc ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_INT_EQUAL (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ABTS_TRUE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_file_close (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_xml_parse_file (int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_1__**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ create_dummy_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ create_dummy_file_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dump_xml (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static void test_xml_parser(abts_case *tc, void *data)
{
    apr_file_t *fd;
    apr_xml_parser *parser;
    apr_xml_doc *doc;
    apr_status_t rv;

    rv = create_dummy_file(tc, p, &fd);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    if (rv != APR_SUCCESS)
        return;

    rv = apr_xml_parse_file(p, &parser, &doc, fd, 2000);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    dump_xml(tc, doc->root, 0);

    rv = apr_file_close(fd);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    rv = create_dummy_file_error(tc, p, &fd);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    if (rv != APR_SUCCESS)
        return;

    rv = apr_xml_parse_file(p, &parser, &doc, fd, 2000);
    ABTS_TRUE(tc, rv != APR_SUCCESS);
}