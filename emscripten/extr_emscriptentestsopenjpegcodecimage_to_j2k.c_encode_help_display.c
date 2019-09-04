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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 

void encode_help_display() {
	fprintf(stdout,"HELP for image_to_j2k\n----\n\n");
	fprintf(stdout,"- the -h option displays this help information on screen\n\n");

/* UniPG>> */
	fprintf(stdout,"List of parameters for the JPEG 2000 "
#ifdef USE_JPWL
		"+ JPWL "
#endif /* USE_JPWL */
		"encoder:\n");
/* <<UniPG */
	fprintf(stdout,"\n");
	fprintf(stdout,"REMARKS:\n");
	fprintf(stdout,"---------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"The markers written to the main_header are : SOC SIZ COD QCD COM.\n");
	fprintf(stdout,"COD and QCD never appear in the tile_header.\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"By default:\n");
	fprintf(stdout,"------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout," * Lossless\n");
	fprintf(stdout," * 1 tile\n");
	fprintf(stdout," * Size of precinct : 2^15 x 2^15 (means 1 precinct)\n");
	fprintf(stdout," * Size of code-block : 64 x 64\n");
	fprintf(stdout," * Number of resolutions: 6\n");
	fprintf(stdout," * No SOP marker in the codestream\n");
	fprintf(stdout," * No EPH marker in the codestream\n");
	fprintf(stdout," * No sub-sampling in x or y direction\n");
	fprintf(stdout," * No mode switch activated\n");
	fprintf(stdout," * Progression order: LRCP\n");
	fprintf(stdout," * No index file\n");
	fprintf(stdout," * No ROI upshifted\n");
	fprintf(stdout," * No offset of the origin of the image\n");
	fprintf(stdout," * No offset of the origin of the tiles\n");
	fprintf(stdout," * Reversible DWT 5-3\n");
/* UniPG>> */
#ifdef USE_JPWL
	fprintf(stdout," * No JPWL protection\n");
#endif /* USE_JPWL */
/* <<UniPG */
	fprintf(stdout,"\n");
	fprintf(stdout,"Parameters:\n");
	fprintf(stdout,"------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Required Parameters (except with -h):\n");
	fprintf(stdout,"One of the two options -ImgDir or -i must be used\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-ImgDir      : Image file Directory path (example ../Images) \n");
	fprintf(stdout,"    When using this option -OutFor must be used\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-OutFor \n");
	fprintf(stdout,"    REQUIRED only if -ImgDir is used\n");
	fprintf(stdout,"	  Need to specify only format without filename <BMP>  \n");
	fprintf(stdout,"    Currently accepts PGM, PPM, PNM, PGX, PNG, BMP, TIF, RAW and TGA formats\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-i           : source file  (-i source.pnm also *.pgm, *.ppm, *.pgx, *png, *.bmp, *.tif, *.raw, *.tga) \n");
	fprintf(stdout,"    When using this option -o must be used\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-o           : destination file (-o dest.j2k or .jp2) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Optional Parameters:\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-h           : display the help information \n ");
	fprintf(stdout,"\n");
	fprintf(stdout,"-cinema2K    : Digital Cinema 2K profile compliant codestream for 2K resolution.(-cinema2k 24 or 48) \n");
  fprintf(stdout,"	  Need to specify the frames per second for a 2K resolution. Only 24 or 48 fps is allowed\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-cinema4K    : Digital Cinema 4K profile compliant codestream for 4K resolution \n");
	fprintf(stdout,"	  Frames per second not required. Default value is 24fps\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-r           : different compression ratios for successive layers (-r 20,10,5)\n ");
	fprintf(stdout,"	         - The rate specified for each quality level is the desired \n");
	fprintf(stdout,"	           compression factor.\n");
	fprintf(stdout,"		   Example: -r 20,10,1 means quality 1: compress 20x, \n");
	fprintf(stdout,"		     quality 2: compress 10x and quality 3: compress lossless\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"               (options -r and -q cannot be used together)\n ");
	fprintf(stdout,"\n");

	fprintf(stdout,"-q           : different psnr for successive layers (-q 30,40,50) \n ");

	fprintf(stdout,"               (options -r and -q cannot be used together)\n ");

	fprintf(stdout,"\n");
	fprintf(stdout,"-n           : number of resolutions (-n 3) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-b           : size of code block (-b 32,32) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-c           : size of precinct (-c 128,128) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-t           : size of tile (-t 512,512) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-p           : progression order (-p LRCP) [LRCP, RLCP, RPCL, PCRL, CPRL] \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-s           : subsampling factor (-s 2,2) [-s X,Y] \n");
	fprintf(stdout,"	     Remark: subsampling bigger than 2 can produce error\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-POC         : Progression order change (-POC T1=0,0,1,5,3,CPRL/T1=5,0,1,6,3,CPRL) \n");
	fprintf(stdout,"      Example: T1=0,0,1,5,3,CPRL \n");
	fprintf(stdout,"			 : Ttilenumber=Resolution num start,Component num start,Layer num end,Resolution num end,Component num end,Progression order\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-SOP         : write SOP marker before each packet \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-EPH         : write EPH marker after each header packet \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-M           : mode switch (-M 3) [1=BYPASS(LAZY) 2=RESET 4=RESTART(TERMALL)\n");
	fprintf(stdout,"                 8=VSC 16=ERTERM(SEGTERM) 32=SEGMARK(SEGSYM)] \n");
	fprintf(stdout,"                 Indicate multiple modes by adding their values. \n");
	fprintf(stdout,"                 ex: RESTART(4) + RESET(2) + SEGMARK(32) = -M 38\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-x           : create an index file *.Idx (-x index_name.Idx) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-ROI         : c=%%d,U=%%d : quantization indices upshifted \n");
	fprintf(stdout,"               for component c=%%d [%%d = 0,1,2]\n");
	fprintf(stdout,"               with a value of U=%%d [0 <= %%d <= 37] (i.e. -ROI c=0,U=25) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-d           : offset of the origin of the image (-d 150,300) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-T           : offset of the origin of the tiles (-T 100,75) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-I           : use the irreversible DWT 9-7 (-I) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-F           : characteristics of the raw input image\n");
	fprintf(stdout,"               -F rawWidth,rawHeight,rawComp,rawBitDepth,s/u (Signed/Unsigned)\n");
	fprintf(stdout,"               Example: -i lena.raw -o lena.j2k -F 512,512,3,8,u\n");
	fprintf(stdout,"\n");
/* UniPG>> */
#ifdef USE_JPWL
	fprintf(stdout,"-W           : adoption of JPWL (Part 11) capabilities (-W params)\n");
	fprintf(stdout,"               The parameters can be written and repeated in any order:\n");
	fprintf(stdout,"               [h<tilepart><=type>,s<tilepart><=method>,a=<addr>,...\n");
	fprintf(stdout,"                ...,z=<size>,g=<range>,p<tilepart:pack><=type>]\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 h selects the header error protection (EPB): 'type' can be\n");
	fprintf(stdout,"                   [0=none 1,absent=predefined 16=CRC-16 32=CRC-32 37-128=RS]\n");
	fprintf(stdout,"                   if 'tilepart' is absent, it is for main and tile headers\n");
	fprintf(stdout,"                   if 'tilepart' is present, it applies from that tile\n");
	fprintf(stdout,"                     onwards, up to the next h<> spec, or to the last tilepart\n");
	fprintf(stdout,"                     in the codestream (max. %d specs)\n", JPWL_MAX_NO_TILESPECS);
	fprintf(stdout,"\n");
	fprintf(stdout,"                 p selects the packet error protection (EEP/UEP with EPBs)\n");
	fprintf(stdout,"                  to be applied to raw data: 'type' can be\n");
	fprintf(stdout,"                   [0=none 1,absent=predefined 16=CRC-16 32=CRC-32 37-128=RS]\n");
	fprintf(stdout,"                   if 'tilepart:pack' is absent, it is from tile 0, packet 0\n");
	fprintf(stdout,"                   if 'tilepart:pack' is present, it applies from that tile\n");
	fprintf(stdout,"                     and that packet onwards, up to the next packet spec\n");
	fprintf(stdout,"                     or to the last packet in the last tilepart in the stream\n");
	fprintf(stdout,"                     (max. %d specs)\n", JPWL_MAX_NO_PACKSPECS);
	fprintf(stdout,"\n");
	fprintf(stdout,"                 s enables sensitivity data insertion (ESD): 'method' can be\n");
	fprintf(stdout,"                   [-1=NO ESD 0=RELATIVE ERROR 1=MSE 2=MSE REDUCTION 3=PSNR\n");
	fprintf(stdout,"                    4=PSNR INCREMENT 5=MAXERR 6=TSE 7=RESERVED]\n");
	fprintf(stdout,"                   if 'tilepart' is absent, it is for main header only\n");
	fprintf(stdout,"                   if 'tilepart' is present, it applies from that tile\n");
	fprintf(stdout,"                     onwards, up to the next s<> spec, or to the last tilepart\n");
	fprintf(stdout,"                     in the codestream (max. %d specs)\n", JPWL_MAX_NO_TILESPECS);
	fprintf(stdout,"\n");
	fprintf(stdout,"                 g determines the addressing mode: <range> can be\n");
	fprintf(stdout,"                   [0=PACKET 1=BYTE RANGE 2=PACKET RANGE]\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 a determines the size of data addressing: <addr> can be\n");
	fprintf(stdout,"                   2/4 bytes (small/large codestreams). If not set, auto-mode\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 z determines the size of sensitivity values: <size> can be\n");
	fprintf(stdout,"                   1/2 bytes, for the transformed pseudo-floating point value\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 ex.:\n");
	fprintf(stdout,"                   h,h0=64,h3=16,h5=32,p0=78,p0:24=56,p1,p3:0=0,p3:20=32,s=0,\n");
	fprintf(stdout,"                     s0=6,s3=-1,a=0,g=1,z=1\n");
	fprintf(stdout,"                 means\n");
	fprintf(stdout,"                   predefined EPB in MH, rs(64,32) from TPH 0 to TPH 2,\n");
	fprintf(stdout,"                   CRC-16 in TPH 3 and TPH 4, CRC-32 in remaining TPHs,\n");
	fprintf(stdout,"                   UEP rs(78,32) for packets 0 to 23 of tile 0,\n");
	fprintf(stdout,"                   UEP rs(56,32) for packs. 24 to the last of tilepart 0,\n");
	fprintf(stdout,"                   UEP rs default for packets of tilepart 1,\n");
	fprintf(stdout,"                   no UEP for packets 0 to 19 of tilepart 3,\n");
	fprintf(stdout,"                   UEP CRC-32 for packs. 20 of tilepart 3 to last tilepart,\n");
	fprintf(stdout,"                   relative sensitivity ESD for MH,\n");
	fprintf(stdout,"                   TSE ESD from TPH 0 to TPH 2, byte range with automatic\n");
	fprintf(stdout,"                   size of addresses and 1 byte for each sensitivity value\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 ex.:\n");
	fprintf(stdout,"                       h,s,p\n");
	fprintf(stdout,"                 means\n");
	fprintf(stdout,"                   default protection to headers (MH and TPHs) as well as\n");
	fprintf(stdout,"                   data packets, one ESD in MH\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 N.B.: use the following recommendations when specifying\n");
	fprintf(stdout,"                       the JPWL parameters list\n");
	fprintf(stdout,"                   - when you use UEP, always pair the 'p' option with 'h'\n");
	fprintf(stdout,"                 \n");
#endif /* USE_JPWL */
/* <<UniPG */
	fprintf(stdout,"IMPORTANT:\n");
	fprintf(stdout,"-----------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"The index file has the structure below:\n");
	fprintf(stdout,"---------------------------------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Image_height Image_width\n");
	fprintf(stdout,"progression order\n");
	fprintf(stdout,"Tiles_size_X Tiles_size_Y\n");
	fprintf(stdout,"Tiles_nb_X Tiles_nb_Y\n");
	fprintf(stdout,"Components_nb\n");
	fprintf(stdout,"Layers_nb\n");
	fprintf(stdout,"decomposition_levels\n");
	fprintf(stdout,"[Precincts_size_X_res_Nr Precincts_size_Y_res_Nr]...\n");
	fprintf(stdout,"   [Precincts_size_X_res_0 Precincts_size_Y_res_0]\n");
	fprintf(stdout,"Main_header_start_position\n");
	fprintf(stdout,"Main_header_end_position\n");
	fprintf(stdout,"Codestream_size\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"INFO ON TILES\n");
	fprintf(stdout,"tileno start_pos end_hd end_tile nbparts disto nbpix disto/nbpix\n");
	fprintf(stdout,"Tile_0 start_pos end_Theader end_pos NumParts TotalDisto NumPix MaxMSE\n");
	fprintf(stdout,"Tile_1   ''           ''        ''        ''       ''    ''      ''\n");
	fprintf(stdout,"...\n");
	fprintf(stdout,"Tile_Nt   ''           ''        ''        ''       ''    ''     ''\n");
	fprintf(stdout,"...\n");
	fprintf(stdout,"TILE 0 DETAILS\n");
	fprintf(stdout,"part_nb tileno num_packs start_pos end_tph_pos end_pos\n");
	fprintf(stdout,"...\n");
	fprintf(stdout,"Progression_string\n");
	fprintf(stdout,"pack_nb tileno layno resno compno precno start_pos end_ph_pos end_pos disto\n");
	fprintf(stdout,"Tpacket_0 Tile layer res. comp. prec. start_pos end_pos disto\n");
	fprintf(stdout,"...\n");
	fprintf(stdout,"Tpacket_Np ''   ''    ''   ''    ''       ''       ''     ''\n");

	fprintf(stdout,"MaxDisto\n");

	fprintf(stdout,"TotalDisto\n\n");
}