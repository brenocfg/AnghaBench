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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int AMF_DATA_TYPE_LONG_STRING ; 
 int AMF_DATA_TYPE_STRING ; 
 int bytestream_get_be16 (int /*<<< orphan*/  const**) ; 
 int bytestream_get_be32 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char const*,int) ; 
 int strlen (char const*) ; 

int ff_amf_match_string(const uint8_t *data, int size, const char *str)
{
    int len = strlen(str);
    int amf_len, type;

    if (size < 1)
        return 0;

    type = *data++;

    if (type != AMF_DATA_TYPE_LONG_STRING &&
        type != AMF_DATA_TYPE_STRING)
        return 0;

    if (type == AMF_DATA_TYPE_LONG_STRING) {
        if ((size -= 4 + 1) < 0)
            return 0;
        amf_len = bytestream_get_be32(&data);
    } else {
        if ((size -= 2 + 1) < 0)
            return 0;
        amf_len = bytestream_get_be16(&data);
    }

    if (amf_len > size)
        return 0;

    if (amf_len != len)
        return 0;

    return !memcmp(data, str, len);
}