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
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int AMFDataType ;

/* Variables and functions */
#define  AMF_DATA_TYPE_ARRAY 137 
#define  AMF_DATA_TYPE_BOOL 136 
#define  AMF_DATA_TYPE_DATE 135 
#define  AMF_DATA_TYPE_LONG_STRING 134 
#define  AMF_DATA_TYPE_MIXEDARRAY 133 
#define  AMF_DATA_TYPE_NULL 132 
#define  AMF_DATA_TYPE_NUMBER 131 
#define  AMF_DATA_TYPE_OBJECT 130 
#define  AMF_DATA_TYPE_OBJECT_END 129 
#define  AMF_DATA_TYPE_STRING 128 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_be64 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int amf_tag_skip(GetByteContext *gb)
{
    AMFDataType type;
    unsigned nb   = -1;
    int parse_key = 1;

    if (bytestream2_get_bytes_left(gb) < 1)
        return -1;

    type = bytestream2_get_byte(gb);
    switch (type) {
    case AMF_DATA_TYPE_NUMBER:
        bytestream2_get_be64(gb);
        return 0;
    case AMF_DATA_TYPE_BOOL:
        bytestream2_get_byte(gb);
        return 0;
    case AMF_DATA_TYPE_STRING:
        bytestream2_skip(gb, bytestream2_get_be16(gb));
        return 0;
    case AMF_DATA_TYPE_LONG_STRING:
        bytestream2_skip(gb, bytestream2_get_be32(gb));
        return 0;
    case AMF_DATA_TYPE_NULL:
        return 0;
    case AMF_DATA_TYPE_DATE:
        bytestream2_skip(gb, 10);
        return 0;
    case AMF_DATA_TYPE_ARRAY:
        parse_key = 0;
    case AMF_DATA_TYPE_MIXEDARRAY:
        nb = bytestream2_get_be32(gb);
    case AMF_DATA_TYPE_OBJECT:
        while (nb-- > 0 || type != AMF_DATA_TYPE_ARRAY) {
            int t;
            if (parse_key) {
                int size = bytestream2_get_be16(gb);
                if (!size) {
                    bytestream2_get_byte(gb);
                    break;
                }
                if (size < 0 || size >= bytestream2_get_bytes_left(gb))
                    return -1;
                bytestream2_skip(gb, size);
            }
            t = amf_tag_skip(gb);
            if (t < 0 || bytestream2_get_bytes_left(gb) <= 0)
                return -1;
        }
        return 0;
    case AMF_DATA_TYPE_OBJECT_END:  return 0;
    default:                        return -1;
    }
}