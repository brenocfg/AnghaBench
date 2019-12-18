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
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 scalar_t__ MZ_ALLOC (scalar_t__) ; 
 scalar_t__ MZ_ENCODING_CODEPAGE_437 ; 
 scalar_t__ MZ_ENCODING_CODEPAGE_932 ; 
 scalar_t__ MZ_ENCODING_CODEPAGE_936 ; 
 scalar_t__ MZ_ENCODING_CODEPAGE_950 ; 
 scalar_t__ MZ_ENCODING_UTF8 ; 
 int /*<<< orphan*/  MZ_FREE (int /*<<< orphan*/ *) ; 
 size_t iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 

uint8_t *mz_os_utf8_string_create(const char *string, int32_t encoding)
{
    iconv_t cd;
    const char *from_encoding = NULL;
    size_t result = 0;
    size_t string_length = 0;
    size_t string_utf8_size = 0;
    uint8_t *string_utf8 = NULL;
    uint8_t *string_utf8_ptr = NULL;

    if (string == NULL)
        return NULL;

    if (encoding == MZ_ENCODING_CODEPAGE_437)
        from_encoding = "CP437";
    else if (encoding == MZ_ENCODING_CODEPAGE_932)
        from_encoding = "CP932";
    else if (encoding == MZ_ENCODING_CODEPAGE_936)
        from_encoding = "CP936";
    else if (encoding == MZ_ENCODING_CODEPAGE_950)
        from_encoding = "CP950";
    else if (encoding == MZ_ENCODING_UTF8)
        from_encoding = "UTF-8";
    else
        return NULL;

    cd = iconv_open("UTF-8", from_encoding);
    if (cd == (iconv_t)-1)
        return NULL;

    string_length = strlen(string);
    string_utf8_size = string_length * 2;
    string_utf8 = (uint8_t *)MZ_ALLOC((int32_t)(string_utf8_size + 1));
    string_utf8_ptr = string_utf8;

    if (string_utf8)
    {
        memset(string_utf8, 0, string_utf8_size + 1);

        result = iconv(cd, (char **)&string, &string_length,
                (char **)&string_utf8_ptr, &string_utf8_size);
    }

    iconv_close(cd);

    if (result == (size_t)-1)
    {
        MZ_FREE(string_utf8);
        string_utf8 = NULL;
    }

    return string_utf8;
}