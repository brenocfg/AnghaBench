#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p; TYPE_3__* cur_elem; scalar_t__ error; } ;
typedef  TYPE_2__ apr_xml_parser ;
struct TYPE_6__ {TYPE_1__* last_child; int /*<<< orphan*/  first_cdata; } ;
typedef  TYPE_3__ apr_xml_elem ;
typedef  int /*<<< orphan*/  apr_text_header ;
struct TYPE_4__ {int /*<<< orphan*/  following_cdata; } ;

/* Variables and functions */
 char* apr_pstrndup (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  apr_text_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void cdata_handler(void *userdata, const char *data, int len)
{
    apr_xml_parser *parser = userdata;
    apr_xml_elem *elem;
    apr_text_header *hdr;
    const char *s;

    /* punt once we find an error */
    if (parser->error)
	return;

    elem = parser->cur_elem;
    s = apr_pstrndup(parser->p, data, len);

    if (elem->last_child == NULL) {
	/* no children yet. this cdata follows the start tag */
	hdr = &elem->first_cdata;
    }
    else {
	/* child elements exist. this cdata follows the last child. */
	hdr = &elem->last_child->following_cdata;
    }

    apr_text_append(parser->p, hdr, s);
}