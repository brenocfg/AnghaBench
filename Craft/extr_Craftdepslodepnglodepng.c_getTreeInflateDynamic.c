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
typedef  int /*<<< orphan*/  HuffmanTree ;

/* Variables and functions */
 size_t* CLCL_ORDER ; 
 int /*<<< orphan*/  ERROR_BREAK (int) ; 
 int /*<<< orphan*/  HuffmanTree_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HuffmanTree_init (int /*<<< orphan*/ *) ; 
 unsigned int HuffmanTree_makeFromLengths (int /*<<< orphan*/ *,unsigned int*,int,int) ; 
 int NUM_CODE_LENGTH_CODES ; 
 int NUM_DEFLATE_CODE_SYMBOLS ; 
 int NUM_DISTANCE_SYMBOLS ; 
 unsigned int huffmanDecodeSymbol (unsigned char const*,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lodepng_free (unsigned int*) ; 
 scalar_t__ lodepng_malloc (int) ; 
 unsigned int readBitsFromStream (size_t*,unsigned char const*,int) ; 

__attribute__((used)) static unsigned getTreeInflateDynamic(HuffmanTree* tree_ll, HuffmanTree* tree_d,
                                      const unsigned char* in, size_t* bp, size_t inlength)
{
  /*make sure that length values that aren't filled in will be 0, or a wrong tree will be generated*/
  unsigned error = 0;
  unsigned n, HLIT, HDIST, HCLEN, i;
  size_t inbitlength = inlength * 8;

  /*see comments in deflateDynamic for explanation of the context and these variables, it is analogous*/
  unsigned* bitlen_ll = 0; /*lit,len code lengths*/
  unsigned* bitlen_d = 0; /*dist code lengths*/
  /*code length code lengths ("clcl"), the bit lengths of the huffman tree used to compress bitlen_ll and bitlen_d*/
  unsigned* bitlen_cl = 0;
  HuffmanTree tree_cl; /*the code tree for code length codes (the huffman tree for compressed huffman trees)*/

  if((*bp) >> 3 >= inlength - 2) return 49; /*error: the bit pointer is or will go past the memory*/

  /*number of literal/length codes + 257. Unlike the spec, the value 257 is added to it here already*/
  HLIT =  readBitsFromStream(bp, in, 5) + 257;
  /*number of distance codes. Unlike the spec, the value 1 is added to it here already*/
  HDIST = readBitsFromStream(bp, in, 5) + 1;
  /*number of code length codes. Unlike the spec, the value 4 is added to it here already*/
  HCLEN = readBitsFromStream(bp, in, 4) + 4;

  HuffmanTree_init(&tree_cl);

  while(!error)
  {
    /*read the code length codes out of 3 * (amount of code length codes) bits*/

    bitlen_cl = (unsigned*)lodepng_malloc(NUM_CODE_LENGTH_CODES * sizeof(unsigned));
    if(!bitlen_cl) ERROR_BREAK(83 /*alloc fail*/);

    for(i = 0; i < NUM_CODE_LENGTH_CODES; i++)
    {
      if(i < HCLEN) bitlen_cl[CLCL_ORDER[i]] = readBitsFromStream(bp, in, 3);
      else bitlen_cl[CLCL_ORDER[i]] = 0; /*if not, it must stay 0*/
    }

    error = HuffmanTree_makeFromLengths(&tree_cl, bitlen_cl, NUM_CODE_LENGTH_CODES, 7);
    if(error) break;

    /*now we can use this tree to read the lengths for the tree that this function will return*/
    bitlen_ll = (unsigned*)lodepng_malloc(NUM_DEFLATE_CODE_SYMBOLS * sizeof(unsigned));
    bitlen_d = (unsigned*)lodepng_malloc(NUM_DISTANCE_SYMBOLS * sizeof(unsigned));
    if(!bitlen_ll || !bitlen_d) ERROR_BREAK(83 /*alloc fail*/);
    for(i = 0; i < NUM_DEFLATE_CODE_SYMBOLS; i++) bitlen_ll[i] = 0;
    for(i = 0; i < NUM_DISTANCE_SYMBOLS; i++) bitlen_d[i] = 0;

    /*i is the current symbol we're reading in the part that contains the code lengths of lit/len and dist codes*/
    i = 0;
    while(i < HLIT + HDIST)
    {
      unsigned code = huffmanDecodeSymbol(in, bp, &tree_cl, inbitlength);
      if(code <= 15) /*a length code*/
      {
        if(i < HLIT) bitlen_ll[i] = code;
        else bitlen_d[i - HLIT] = code;
        i++;
      }
      else if(code == 16) /*repeat previous*/
      {
        unsigned replength = 3; /*read in the 2 bits that indicate repeat length (3-6)*/
        unsigned value; /*set value to the previous code*/

        if(*bp >= inbitlength) ERROR_BREAK(50); /*error, bit pointer jumps past memory*/
        if (i == 0) ERROR_BREAK(54); /*can't repeat previous if i is 0*/

        replength += readBitsFromStream(bp, in, 2);

        if(i < HLIT + 1) value = bitlen_ll[i - 1];
        else value = bitlen_d[i - HLIT - 1];
        /*repeat this value in the next lengths*/
        for(n = 0; n < replength; n++)
        {
          if(i >= HLIT + HDIST) ERROR_BREAK(13); /*error: i is larger than the amount of codes*/
          if(i < HLIT) bitlen_ll[i] = value;
          else bitlen_d[i - HLIT] = value;
          i++;
        }
      }
      else if(code == 17) /*repeat "0" 3-10 times*/
      {
        unsigned replength = 3; /*read in the bits that indicate repeat length*/
        if(*bp >= inbitlength) ERROR_BREAK(50); /*error, bit pointer jumps past memory*/

        replength += readBitsFromStream(bp, in, 3);

        /*repeat this value in the next lengths*/
        for(n = 0; n < replength; n++)
        {
          if(i >= HLIT + HDIST) ERROR_BREAK(14); /*error: i is larger than the amount of codes*/

          if(i < HLIT) bitlen_ll[i] = 0;
          else bitlen_d[i - HLIT] = 0;
          i++;
        }
      }
      else if(code == 18) /*repeat "0" 11-138 times*/
      {
        unsigned replength = 11; /*read in the bits that indicate repeat length*/
        if(*bp >= inbitlength) ERROR_BREAK(50); /*error, bit pointer jumps past memory*/

        replength += readBitsFromStream(bp, in, 7);

        /*repeat this value in the next lengths*/
        for(n = 0; n < replength; n++)
        {
          if(i >= HLIT + HDIST) ERROR_BREAK(15); /*error: i is larger than the amount of codes*/

          if(i < HLIT) bitlen_ll[i] = 0;
          else bitlen_d[i - HLIT] = 0;
          i++;
        }
      }
      else /*if(code == (unsigned)(-1))*/ /*huffmanDecodeSymbol returns (unsigned)(-1) in case of error*/
      {
        if(code == (unsigned)(-1))
        {
          /*return error code 10 or 11 depending on the situation that happened in huffmanDecodeSymbol
          (10=no endcode, 11=wrong jump outside of tree)*/
          error = (*bp) > inbitlength ? 10 : 11;
        }
        else error = 16; /*unexisting code, this can never happen*/
        break;
      }
    }
    if(error) break;

    if(bitlen_ll[256] == 0) ERROR_BREAK(64); /*the length of the end code 256 must be larger than 0*/

    /*now we've finally got HLIT and HDIST, so generate the code trees, and the function is done*/
    error = HuffmanTree_makeFromLengths(tree_ll, bitlen_ll, NUM_DEFLATE_CODE_SYMBOLS, 15);
    if(error) break;
    error = HuffmanTree_makeFromLengths(tree_d, bitlen_d, NUM_DISTANCE_SYMBOLS, 15);

    break; /*end of error-while*/
  }

  lodepng_free(bitlen_cl);
  lodepng_free(bitlen_ll);
  lodepng_free(bitlen_d);
  HuffmanTree_cleanup(&tree_cl);

  return error;
}