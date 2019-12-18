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
typedef  int uint8_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ MZ_EXIST_ERROR ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_SEEK_SET ; 
 int MZ_STREAM_FIND_SIZE ; 
 scalar_t__ memcmp (int*,void const*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (int*,int*,scalar_t__) ; 
 scalar_t__ mz_stream_read (void*,int*,scalar_t__) ; 
 scalar_t__ mz_stream_seek (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_tell (void*) ; 

int32_t mz_stream_find(void *stream, const void *find, int32_t find_size, int64_t max_seek, int64_t *position)
{
    uint8_t buf[MZ_STREAM_FIND_SIZE];
    int32_t buf_pos = 0;
    int32_t read_size = sizeof(buf);
    int32_t read = 0;
    int64_t read_pos = 0;
    int64_t start_pos = 0;
    int64_t disk_pos = 0;
    int32_t i = 0;
    uint8_t first = 1;
    int32_t err = MZ_OK;

    if (stream == NULL || find == NULL || position == NULL)
        return MZ_PARAM_ERROR;
    if (find_size < 0 || find_size >= (int32_t)sizeof(buf))
        return MZ_PARAM_ERROR;

    *position = -1;

    start_pos = mz_stream_tell(stream);

    while (read_pos < max_seek)
    {
        if (read_size > (int32_t)(max_seek - read_pos - buf_pos))
            read_size = (int32_t)(max_seek - read_pos - buf_pos);

        read = mz_stream_read(stream, buf + buf_pos, read_size);
        if ((read < 0) || (read + buf_pos < find_size))
            break;

        for (i = 0; i <= read + buf_pos - find_size; i += 1)
        {
            if (memcmp(&buf[i], find, find_size) != 0)
                continue;

            disk_pos = mz_stream_tell(stream);

            /* Seek to position on disk where the data was found */
            err = mz_stream_seek(stream, disk_pos - ((int64_t)read + buf_pos - i), MZ_SEEK_SET);
            if (err != MZ_OK)
                return MZ_EXIST_ERROR;

            *position = start_pos + read_pos + i;
            return MZ_OK;
        }

        if (first)
        {
            read -= find_size;
            read_size -= find_size;
            buf_pos = find_size;
            first = 0;
        }

        memmove(buf, buf + read, find_size);
        read_pos += read;
    }

    return MZ_EXIST_ERROR;
}