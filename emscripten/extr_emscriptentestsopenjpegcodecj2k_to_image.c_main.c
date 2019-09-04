#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ color_space; unsigned char* icc_profile_buf; scalar_t__ icc_profile_len; } ;
typedef  TYPE_1__ opj_image_t ;
struct TYPE_26__ {int set_imgdir; int /*<<< orphan*/  imgdirpath; int /*<<< orphan*/  info_handler; int /*<<< orphan*/  warning_handler; int /*<<< orphan*/  error_handler; } ;
typedef  TYPE_2__ opj_event_mgr_t ;
struct TYPE_27__ {char* infile; int decod_format; int cod_format; char* outfile; } ;
typedef  TYPE_3__ opj_dparameters_t ;
typedef  int /*<<< orphan*/  opj_dinfo_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
typedef  TYPE_2__ img_fol_t ;
struct TYPE_28__ {char* filename_buf; char** filename; } ;
typedef  TYPE_5__ dircnt_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  BMP_DFMT 135 
 scalar_t__ CLRSPC_SYCC ; 
 int /*<<< orphan*/  CODEC_J2K ; 
 int /*<<< orphan*/  CODEC_JP2 ; 
 int /*<<< orphan*/  CODEC_JPT ; 
#define  J2K_CFMT 134 
#define  JP2_CFMT 133 
#define  JPT_CFMT 132 
 int OPJ_PATH_LEN ; 
#define  PGX_DFMT 131 
#define  PXM_DFMT 130 
#define  RAW_DFMT 129 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
#define  TGA_DFMT 128 
 int /*<<< orphan*/  color_sycc_to_rgb (TYPE_1__*) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ get_next_file (int,TYPE_5__*,TYPE_2__*,TYPE_3__*) ; 
 int get_num_images (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imagetobmp (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  imagetopgx (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  imagetopnm (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  imagetoraw (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  imagetotga (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  info_callback ; 
 int load_images (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_cio_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opj_cio_open (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/ * opj_create_decompress (int /*<<< orphan*/ ) ; 
 TYPE_1__* opj_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* opj_decode_with_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_destroy_cstr_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_destroy_decompress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_image_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_set_default_decoder_parameters (TYPE_3__*) ; 
 int /*<<< orphan*/  opj_set_event_mgr (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_setup_decoder (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int parse_cmdline_decoder (int,char**,TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warning_callback ; 
 char write_index_file (int /*<<< orphan*/ *,char*) ; 

int main(int argc, char **argv) {
	opj_dparameters_t parameters;	/* decompression parameters */
	img_fol_t img_fol;
	opj_event_mgr_t event_mgr;		/* event manager */
	opj_image_t *image = NULL;
	FILE *fsrc = NULL;
	unsigned char *src = NULL;
	int file_length;
	int num_images;
	int i,imageno;
	dircnt_t *dirptr;
	opj_dinfo_t* dinfo = NULL;	/* handle to a decompressor */
	opj_cio_t *cio = NULL;
	opj_codestream_info_t cstr_info;  /* Codestream information structure */
	char indexfilename[OPJ_PATH_LEN];	/* index file name */

	/* configure the event callbacks (not required) */
	memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
	event_mgr.error_handler = error_callback;
	event_mgr.warning_handler = warning_callback;
	event_mgr.info_handler = info_callback;

	/* set decoding parameters to default values */
	opj_set_default_decoder_parameters(&parameters);

	/* Initialize indexfilename and img_fol */
	*indexfilename = 0;
	memset(&img_fol,0,sizeof(img_fol_t));

	/* parse input and get user encoding parameters */
	if(parse_cmdline_decoder(argc, argv, &parameters,&img_fol, indexfilename) == 1) {
		return 1;
	}

	/* Initialize reading of directory */
	if(img_fol.set_imgdir==1){	
		num_images=get_num_images(img_fol.imgdirpath);

		dirptr=(dircnt_t*)malloc(sizeof(dircnt_t));
		if(dirptr){
			dirptr->filename_buf = (char*)malloc(num_images*OPJ_PATH_LEN*sizeof(char));	// Stores at max 10 image file names
			dirptr->filename = (char**) malloc(num_images*sizeof(char*));

			if(!dirptr->filename_buf){
				return 1;
			}
			for(i=0;i<num_images;i++){
				dirptr->filename[i] = dirptr->filename_buf + i*OPJ_PATH_LEN;
			}
		}
		if(load_images(dirptr,img_fol.imgdirpath)==1){
			return 1;
		}
		if (num_images==0){
			fprintf(stdout,"Folder is empty\n");
			return 1;
		}
	}else{
		num_images=1;
	}

	/*Encoding image one by one*/
	for(imageno = 0; imageno < num_images ; imageno++)	{
		image = NULL;
		fprintf(stderr,"\n");

		if(img_fol.set_imgdir==1){
			if (get_next_file(imageno, dirptr,&img_fol, &parameters)) {
				fprintf(stderr,"skipping file...\n");
				continue;
			}
		}

		/* read the input file and put it in memory */
		/* ---------------------------------------- */
		fsrc = fopen(parameters.infile, "rb");
		if (!fsrc) {
			fprintf(stderr, "ERROR -> failed to open %s for reading\n", parameters.infile);
			return 1;
		}
		fseek(fsrc, 0, SEEK_END);
		file_length = ftell(fsrc);
		fseek(fsrc, 0, SEEK_SET);
		src = (unsigned char *) malloc(file_length);
		fread(src, 1, file_length, fsrc);
		fclose(fsrc);

		/* decode the code-stream */
		/* ---------------------- */

		switch(parameters.decod_format) {
		case J2K_CFMT:
		{
			/* JPEG-2000 codestream */

			/* get a decoder handle */
			dinfo = opj_create_decompress(CODEC_J2K);

			/* catch events using our callbacks and give a local context */
			opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

			/* setup the decoder decoding parameters using user parameters */
			opj_setup_decoder(dinfo, &parameters);

			/* open a byte stream */
			cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

			/* decode the stream and fill the image structure */
			if (*indexfilename)				// If need to extract codestream information
				image = opj_decode_with_info(dinfo, cio, &cstr_info);
			else
				image = opj_decode(dinfo, cio);
			if(!image) {
				fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
				opj_destroy_decompress(dinfo);
				opj_cio_close(cio);
				return 1;
			}

			/* close the byte stream */
			opj_cio_close(cio);

			/* Write the index to disk */
			if (*indexfilename) {
				char bSuccess;
				bSuccess = write_index_file(&cstr_info, indexfilename);
				if (bSuccess) {
					fprintf(stderr, "Failed to output index file\n");
				}
			}
		}
		break;

		case JP2_CFMT:
		{
			/* JPEG 2000 compressed image data */

			/* get a decoder handle */
			dinfo = opj_create_decompress(CODEC_JP2);

			/* catch events using our callbacks and give a local context */
			opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

			/* setup the decoder decoding parameters using the current image and user parameters */
			opj_setup_decoder(dinfo, &parameters);

			/* open a byte stream */
			cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

			/* decode the stream and fill the image structure */
			if (*indexfilename)				// If need to extract codestream information
				image = opj_decode_with_info(dinfo, cio, &cstr_info);
			else
				image = opj_decode(dinfo, cio);			
			if(!image) {
				fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
				opj_destroy_decompress(dinfo);
				opj_cio_close(cio);
				return 1;
			}

			/* close the byte stream */
			opj_cio_close(cio);

			/* Write the index to disk */
			if (*indexfilename) {
				char bSuccess;
				bSuccess = write_index_file(&cstr_info, indexfilename);
				if (bSuccess) {
					fprintf(stderr, "Failed to output index file\n");
				}
			}
		}
		break;

		case JPT_CFMT:
		{
			/* JPEG 2000, JPIP */

			/* get a decoder handle */
			dinfo = opj_create_decompress(CODEC_JPT);

			/* catch events using our callbacks and give a local context */
			opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

			/* setup the decoder decoding parameters using user parameters */
			opj_setup_decoder(dinfo, &parameters);

			/* open a byte stream */
			cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

			/* decode the stream and fill the image structure */
			if (*indexfilename)				// If need to extract codestream information
				image = opj_decode_with_info(dinfo, cio, &cstr_info);
			else
				image = opj_decode(dinfo, cio);
			if(!image) {
				fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
				opj_destroy_decompress(dinfo);
				opj_cio_close(cio);
				return 1;
			}

			/* close the byte stream */
			opj_cio_close(cio);

			/* Write the index to disk */
			if (*indexfilename) {
				char bSuccess;
				bSuccess = write_index_file(&cstr_info, indexfilename);
				if (bSuccess) {
					fprintf(stderr, "Failed to output index file\n");
				}
			}
		}
		break;

		default:
			fprintf(stderr, "skipping file..\n");
			continue;
	}

		/* free the memory containing the code-stream */
		free(src);
		src = NULL;

	if(image->color_space == CLRSPC_SYCC)
   {
	color_sycc_to_rgb(image);
   }

	if(image->icc_profile_buf)
   {
#if defined(HAVE_LIBLCMS1) || defined(HAVE_LIBLCMS2)
	color_apply_icc_profile(image);
#endif

	free(image->icc_profile_buf);
	image->icc_profile_buf = NULL; image->icc_profile_len = 0;
   }

		/* create output image */
		/* ------------------- */
		switch (parameters.cod_format) {
		case PXM_DFMT:			/* PNM PGM PPM */
			if (imagetopnm(image, parameters.outfile)) {
				fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
			}
			break;

		case PGX_DFMT:			/* PGX */
			if(imagetopgx(image, parameters.outfile)){
				fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
			}
			break;

		case BMP_DFMT:			/* BMP */
			if(imagetobmp(image, parameters.outfile)){
				fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
			}
			break;
#ifdef HAVE_LIBTIFF
		case TIF_DFMT:			/* TIFF */
			if(imagetotif(image, parameters.outfile)){
				fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
			}
			break;
#endif /* HAVE_LIBTIFF */
		case RAW_DFMT:			/* RAW */
			if(imagetoraw(image, parameters.outfile)){
				fprintf(stdout,"Error generating raw file. Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
			}
			break;

		case TGA_DFMT:			/* TGA */
			if(imagetotga(image, parameters.outfile)){
				fprintf(stdout,"Error generating tga file. Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
			}
			break;
#ifdef HAVE_LIBPNG
		case PNG_DFMT:			/* PNG */
			if(imagetopng(image, parameters.outfile)){
				fprintf(stdout,"Error generating png file. Outfile %s not generated\n",parameters.outfile);
			}
			else {
				fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
			}
			break;
#endif /* HAVE_LIBPNG */
/* Can happen if output file is TIFF or PNG
 * and HAVE_LIBTIF or HAVE_LIBPNG is undefined
*/
			default:
				fprintf(stderr,"Outfile %s not generated\n",parameters.outfile);
		}

		/* free remaining structures */
		if(dinfo) {
			opj_destroy_decompress(dinfo);
		}
		/* free codestream information structure */
		if (*indexfilename)	
			opj_destroy_cstr_info(&cstr_info);
		/* free image data structure */
		opj_image_destroy(image);

	}
	return 0;
}