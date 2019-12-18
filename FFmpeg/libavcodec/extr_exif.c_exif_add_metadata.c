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
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  TIFF_BYTE 138 
#define  TIFF_DOUBLE 137 
#define  TIFF_LONG 136 
#define  TIFF_RATIONAL 135 
#define  TIFF_SBYTE 134 
#define  TIFF_SHORT 133 
#define  TIFF_SLONG 132 
#define  TIFF_SRATIONAL 131 
#define  TIFF_SSHORT 130 
#define  TIFF_STRING 129 
#define  TIFF_UNDEFINED 128 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (void*,char*,int) ; 
 int ff_tadd_bytes_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int ff_tadd_doubles_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int ff_tadd_long_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int ff_tadd_rational_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int ff_tadd_shorts_metadata (int,char const*,char const*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **) ; 
 int ff_tadd_string_metadata (int,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int exif_add_metadata(void *logctx, int count, int type,
                             const char *name, const char *sep,
                             GetByteContext *gb, int le,
                             AVDictionary **metadata)
{
    switch(type) {
    case 0:
        av_log(logctx, AV_LOG_WARNING,
               "Invalid TIFF tag type 0 found for %s with size %d\n",
               name, count);
        return 0;
    case TIFF_DOUBLE   : return ff_tadd_doubles_metadata(count, name, sep, gb, le, metadata);
    case TIFF_SSHORT   : return ff_tadd_shorts_metadata(count, name, sep, gb, le, 1, metadata);
    case TIFF_SHORT    : return ff_tadd_shorts_metadata(count, name, sep, gb, le, 0, metadata);
    case TIFF_SBYTE    : return ff_tadd_bytes_metadata(count, name, sep, gb, le, 1, metadata);
    case TIFF_BYTE     :
    case TIFF_UNDEFINED: return ff_tadd_bytes_metadata(count, name, sep, gb, le, 0, metadata);
    case TIFF_STRING   : return ff_tadd_string_metadata(count, name, gb, le, metadata);
    case TIFF_SRATIONAL:
    case TIFF_RATIONAL : return ff_tadd_rational_metadata(count, name, sep, gb, le, metadata);
    case TIFF_SLONG    :
    case TIFF_LONG     : return ff_tadd_long_metadata(count, name, sep, gb, le, metadata);
    default:
        avpriv_request_sample(logctx, "TIFF tag type (%u)", type);
        return 0;
    };
}