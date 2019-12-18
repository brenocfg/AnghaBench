#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ array; } ;
struct TYPE_6__ {TYPE_1__ v; } ;
struct TYPE_7__ {TYPE_2__ attr_value; int /*<<< orphan*/  attr_len_type; } ;
typedef  TYPE_3__ tSDP_DISC_ATTR ;
typedef  int UINT16 ;

/* Variables and functions */
 int SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void SDP_AttrStringCopy(char *dst, tSDP_DISC_ATTR *p_attr, UINT16 dst_size)
{
    if ( dst == NULL ) {
        return;
    }
    if ( p_attr ) {
        UINT16 len = SDP_DISC_ATTR_LEN(p_attr->attr_len_type);
        if ( len > dst_size - 1 ) {
            len = dst_size - 1;
        }
        memcpy(dst, (char *)p_attr->attr_value.v.array, len);
        dst[len] = '\0';
    } else {
        dst[0] = '\0';
    }
}