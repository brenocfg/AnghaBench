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
typedef  int /*<<< orphan*/  tSDP_ATTRIBUTE ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT16 ;

/* Variables and functions */
 int SDP_MAX_ATTR_LEN ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 scalar_t__ osi_malloc (int) ; 
 int /*<<< orphan*/  sdpu_build_attrib_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sdpu_get_attrib_entry_len (int /*<<< orphan*/ *) ; 

UINT8 *sdpu_build_partial_attrib_entry (UINT8 *p_out, tSDP_ATTRIBUTE *p_attr, UINT16 len, UINT16 *offset)
{
    UINT8   *p_attr_buff;
    UINT8   *p_tmp_attr;
    size_t  len_to_copy;
    UINT16  attr_len;

    if ((p_attr_buff = (UINT8 *) osi_malloc(sizeof(UINT8) * SDP_MAX_ATTR_LEN )) == NULL) {
        SDP_TRACE_ERROR("sdpu_build_partial_attrib_entry cannot get a buffer!\n");
        return NULL;
    }
    p_tmp_attr = p_attr_buff;

    sdpu_build_attrib_entry(p_tmp_attr, p_attr);
    attr_len = sdpu_get_attrib_entry_len(p_attr);

    len_to_copy = ((attr_len - *offset) < len) ? (attr_len - *offset) : len;

    memcpy(p_out, &p_attr_buff[*offset], len_to_copy);

    p_out = &p_out[len_to_copy];
    *offset += len_to_copy;

    osi_free(p_attr_buff);
    return p_out;
}