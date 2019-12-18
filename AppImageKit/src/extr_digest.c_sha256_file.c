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
typedef  int byte ;
typedef  int /*<<< orphan*/  SHA256_CTX ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA256_Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (int*,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int* malloc (int const) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int sha256_file(char *path, char outputBuffer[65], int skip_offset, int skip_length)
{
    FILE *file = fopen(path, "rb");
    if(!file) return(1);
    byte hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    const int bufSize = 1024*1024;
    byte *buffer = malloc(bufSize);
    int bytesRead = 0;
    if(!buffer) {
        fclose(file);
        return ENOMEM;
    }

    int totalBytesRead = 0;
    if(skip_offset <= bufSize){
        bytesRead = fread(buffer, 1, skip_offset, file);
        totalBytesRead += bytesRead;
        // printf("totalBytesRead: %i\n", totalBytesRead);
        // printf("bytesRead: %i\n", bytesRead);
        SHA256_Update(&sha256, buffer, bytesRead);
    } else {
        int stillToRead = skip_offset-bytesRead;
        // printf("Initial stillToRead: %i\n", stillToRead);
        int readThisTime;

        if(stillToRead>bufSize){
            readThisTime = bufSize;
        } else {
            readThisTime = stillToRead;
        }
        while((bytesRead = fread(buffer, 1, readThisTime, file)))
        {
            totalBytesRead += bytesRead;
            // printf("totalBytesRead: %i\n", totalBytesRead);
            // printf("readThisTime: %i\n", readThisTime);
            // printf("bytesRead: %i\n", bytesRead);
            SHA256_Update(&sha256, buffer, bytesRead);
            stillToRead = skip_offset-totalBytesRead;
            // printf("stillToRead: %i\n", stillToRead);

            if(stillToRead>bufSize){
                readThisTime = bufSize;
            } else {
                readThisTime = stillToRead;
            }
        }
    }

    fseek(file, skip_offset+skip_length, SEEK_SET);
    
    /* Instead of the skipped area, calculate the sha256 of the same amount if 0x00s */
    int i = 0;
    for(i = 0; i < skip_length; i++) {
        SHA256_Update(&sha256, "\0", 1);
        totalBytesRead += 1;
    }
        
    while((bytesRead = fread(buffer, 1, bufSize, file)))
    {
        totalBytesRead += bytesRead;
        // printf("totalBytesRead: %i\n", totalBytesRead);
        // printf("bytesRead: %i\n", bytesRead);
        SHA256_Update(&sha256, buffer, bytesRead);
    }
    SHA256_Final(hash, &sha256);

    // fprintf(stderr, "totalBytesRead: %i\n", totalBytesRead);
    
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;

    fclose(file);
    free(buffer);
    
    return 0;
}