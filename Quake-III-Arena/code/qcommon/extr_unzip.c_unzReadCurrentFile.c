#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ compressed_size; } ;
struct TYPE_6__ {TYPE_1__ cur_file_info; TYPE_3__* pfile_in_zip_read; } ;
typedef  TYPE_2__ unz_s ;
typedef  int /*<<< orphan*/ * unzFile ;
typedef  scalar_t__ uLong ;
typedef  scalar_t__ uInt ;
struct TYPE_8__ {scalar_t__ avail_out; scalar_t__ avail_in; scalar_t__ total_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
struct TYPE_7__ {unsigned int rest_read_uncompressed; scalar_t__ rest_read_compressed; scalar_t__ pos_in_zipfile; scalar_t__ byte_before_the_zipfile; scalar_t__ compression_method; TYPE_4__ stream; int /*<<< orphan*/ * read_buffer; int /*<<< orphan*/  file; } ;
typedef  TYPE_3__ file_in_zip_read_info_s ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ UNZ_BUFSIZE ; 
 int UNZ_END_OF_LIST_OF_FILE ; 
 int UNZ_EOF ; 
 int UNZ_ERRNO ; 
 int UNZ_OK ; 
 int UNZ_PARAMERROR ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int Z_SYNC_FLUSH ; 
 int fread (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int inflate (TYPE_4__*,int) ; 

extern int unzReadCurrentFile  (unzFile file, void *buf, unsigned len)
{
	int err=UNZ_OK;
	uInt iRead = 0;
	unz_s* s;
	file_in_zip_read_info_s* pfile_in_zip_read_info;
	if (file==NULL)
		return UNZ_PARAMERROR;
	s=(unz_s*)file;
    pfile_in_zip_read_info=s->pfile_in_zip_read;

	if (pfile_in_zip_read_info==NULL)
		return UNZ_PARAMERROR;


	if ((pfile_in_zip_read_info->read_buffer == NULL))
		return UNZ_END_OF_LIST_OF_FILE;
	if (len==0)
		return 0;

	pfile_in_zip_read_info->stream.next_out = (Byte*)buf;

	pfile_in_zip_read_info->stream.avail_out = (uInt)len;
	
	if (len>pfile_in_zip_read_info->rest_read_uncompressed)
		pfile_in_zip_read_info->stream.avail_out = 
		  (uInt)pfile_in_zip_read_info->rest_read_uncompressed;

	while (pfile_in_zip_read_info->stream.avail_out>0)
	{
		if ((pfile_in_zip_read_info->stream.avail_in==0) &&
            (pfile_in_zip_read_info->rest_read_compressed>0))
		{
			uInt uReadThis = UNZ_BUFSIZE;
			if (pfile_in_zip_read_info->rest_read_compressed<uReadThis)
				uReadThis = (uInt)pfile_in_zip_read_info->rest_read_compressed;
			if (uReadThis == 0)
				return UNZ_EOF;
			if (s->cur_file_info.compressed_size == pfile_in_zip_read_info->rest_read_compressed)
				if (fseek(pfile_in_zip_read_info->file,
						  pfile_in_zip_read_info->pos_in_zipfile + 
							 pfile_in_zip_read_info->byte_before_the_zipfile,SEEK_SET)!=0)
					return UNZ_ERRNO;
			if (fread(pfile_in_zip_read_info->read_buffer,uReadThis,1,
                         pfile_in_zip_read_info->file)!=1)
				return UNZ_ERRNO;
			pfile_in_zip_read_info->pos_in_zipfile += uReadThis;

			pfile_in_zip_read_info->rest_read_compressed-=uReadThis;
			
			pfile_in_zip_read_info->stream.next_in = 
                (Byte*)pfile_in_zip_read_info->read_buffer;
			pfile_in_zip_read_info->stream.avail_in = (uInt)uReadThis;
		}

		if (pfile_in_zip_read_info->compression_method==0)
		{
			uInt uDoCopy,i ;
			if (pfile_in_zip_read_info->stream.avail_out < 
                            pfile_in_zip_read_info->stream.avail_in)
				uDoCopy = pfile_in_zip_read_info->stream.avail_out ;
			else
				uDoCopy = pfile_in_zip_read_info->stream.avail_in ;
				
			for (i=0;i<uDoCopy;i++)
				*(pfile_in_zip_read_info->stream.next_out+i) =
                        *(pfile_in_zip_read_info->stream.next_in+i);
					
//			pfile_in_zip_read_info->crc32 = crc32(pfile_in_zip_read_info->crc32,
//								pfile_in_zip_read_info->stream.next_out,
//								uDoCopy);
			pfile_in_zip_read_info->rest_read_uncompressed-=uDoCopy;
			pfile_in_zip_read_info->stream.avail_in -= uDoCopy;
			pfile_in_zip_read_info->stream.avail_out -= uDoCopy;
			pfile_in_zip_read_info->stream.next_out += uDoCopy;
			pfile_in_zip_read_info->stream.next_in += uDoCopy;
            pfile_in_zip_read_info->stream.total_out += uDoCopy;
			iRead += uDoCopy;
		}
		else
		{
			uLong uTotalOutBefore,uTotalOutAfter;
			const Byte *bufBefore;
			uLong uOutThis;
			int flush=Z_SYNC_FLUSH;

			uTotalOutBefore = pfile_in_zip_read_info->stream.total_out;
			bufBefore = pfile_in_zip_read_info->stream.next_out;

			/*
			if ((pfile_in_zip_read_info->rest_read_uncompressed ==
			         pfile_in_zip_read_info->stream.avail_out) &&
				(pfile_in_zip_read_info->rest_read_compressed == 0))
				flush = Z_FINISH;
			*/
			err=inflate(&pfile_in_zip_read_info->stream,flush);

			uTotalOutAfter = pfile_in_zip_read_info->stream.total_out;
			uOutThis = uTotalOutAfter-uTotalOutBefore;
			
//			pfile_in_zip_read_info->crc32 = 
//                crc32(pfile_in_zip_read_info->crc32,bufBefore,
//                        (uInt)(uOutThis));

			pfile_in_zip_read_info->rest_read_uncompressed -=
                uOutThis;

			iRead += (uInt)(uTotalOutAfter - uTotalOutBefore);
            
			if (err==Z_STREAM_END)
				return (iRead==0) ? UNZ_EOF : iRead;
			if (err!=Z_OK) 
				break;
		}
	}

	if (err==Z_OK)
		return iRead;
	return err;
}