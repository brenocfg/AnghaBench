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
struct TYPE_3__ {char* mime_type; scalar_t__* description; } ;
typedef  scalar_t__ FLAC__byte ;
typedef  int FLAC__bool ;
typedef  TYPE_1__ FLAC__StreamMetadata_Picture ;

/* Variables and functions */
 unsigned int utf8len_ (scalar_t__*) ; 

FLAC__bool FLAC__format_picture_is_legal(const FLAC__StreamMetadata_Picture *picture, const char **violation)
{
	char *p;
	FLAC__byte *b;

	for(p = picture->mime_type; *p; p++) {
		if(*p < 0x20 || *p > 0x7e) {
			if(violation) *violation = "MIME type string must contain only printable ASCII characters (0x20-0x7e)";
			return false;
		}
	}

	for(b = picture->description; *b; ) {
		unsigned n = utf8len_(b);
		if(n == 0) {
			if(violation) *violation = "description string must be valid UTF-8";
			return false;
		}
		b += n;
	}

	return true;
}