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
 int /*<<< orphan*/  BitConv (int,int,char*) ; 
 int /*<<< orphan*/  Fetch (int,char*) ; 
 int /*<<< orphan*/  Save (int,char*) ; 
 int* bitsreal ; 
 char** check ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char** str ; 

main()
{
 int srcbits,destbits,srcchannels,destchannels;
 int srcbo,destbo;

 puts("void SexiALI_Convert(SexyAL_format *srcformat, SexyAL_format *destformat, void *vdest, void *vsrc, uint32_t frames)");
 puts("{");

 for(srcbits=0;srcbits<8;srcbits++)
 {
  printf("if(srcformat->sampformat == %s)\n{\n",check[srcbits]);

  printf("%s* src=vsrc;\n",str[srcbits]);

  for(destbits=0;destbits<8;destbits++)
  {
   printf("if(destformat->sampformat == %s)\n{\n",check[destbits]);

   printf("%s* dest=vdest;\n",str[destbits]);

   for(srcchannels=0;srcchannels<2;srcchannels++)
   {
    printf("if(srcformat->channels == %c)\n{\n",'1'+srcchannels);
    for(destchannels=0;destchannels<2;destchannels++)
    {
     printf("if(destformat->channels == %c)\n{\n",'1'+destchannels);
     for(srcbo=0;srcbo<2;srcbo++)
     {
      printf("if(srcformat->byteorder == %d)\n{\n",srcbo);
      for(destbo=0;destbo<2;destbo++)
      {
       printf("if(destformat->byteorder == %d)\n{\n",destbo);
       //printf("if(srcformat->sampformat==%s && destformat->sameck[srcbits],check[destbits]);
       printf("while(frames--)\n{\n");

       puts("int32_t tmp;");
       if(srcchannels)
	puts("int32_t tmp2;");

       Fetch(srcbits,"");

       if(srcbo) 
       {
        if(bitsreal[srcbits]==16)
         puts("FLIP16(tmp);");
        else
         puts("FLIP32(tmp);");
       }

       if(srcchannels) 
       {
        Fetch(srcbits,"2");
        if(srcbo) 
        {
         if(bitsreal[srcbits]==16)
          puts("FLIP16(tmp2);");
         else
          puts("FLIP32(tmp2);");
        } 
       }

       BitConv(srcbits,destbits,"");

       if(srcchannels) BitConv(srcbits,destbits,"2");

       if(destbo)
       { 
        if(bitsreal[srcbits]==16)
         puts("FLIP16(tmp);");
        else
         puts("FLIP32(tmp);");
        if(srcchannels && destchannels && destbo)
        {
         if(bitsreal[srcbits]==16)
          puts("FLIP16(tmp2);");   
         else
          puts("FLIP32(tmp2);");
        }
       }

       if(srcchannels && !destchannels)
        printf("tmp = (tmp+tmp2)>>1;\n");

       Save(destbits,"");
       if(!srcchannels && destchannels)
        Save(destbits,"");

       if(srcchannels && destchannels)
        Save(destbits,"2");

       puts("}");
       puts("}");
      } // destbo
      puts("}");
     } // srcbo
     puts("}");
    }
    puts("}");
   }
   puts("}");
  }
  puts("}");
 }

 puts("}");
}