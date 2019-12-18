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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  lmp_subversion; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  lmp_version; int /*<<< orphan*/  hci_revision; int /*<<< orphan*/  hci_version; } ;
typedef  TYPE_1__ bt_version_t ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_READ_LOCAL_VERSION_INFO ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_command_complete_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_read_local_version_info_response(
    BT_HDR *response,
    bt_version_t *bt_version)
{

    uint8_t *stream = read_command_complete_header(response, HCI_READ_LOCAL_VERSION_INFO, 8 /* bytes after */);
    assert(stream != NULL);
    STREAM_TO_UINT8(bt_version->hci_version, stream);
    STREAM_TO_UINT16(bt_version->hci_revision, stream);
    STREAM_TO_UINT8(bt_version->lmp_version, stream);
    STREAM_TO_UINT16(bt_version->manufacturer, stream);
    STREAM_TO_UINT16(bt_version->lmp_subversion, stream);

    osi_free(response);
}